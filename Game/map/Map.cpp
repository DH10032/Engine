#include "Map.h"

namespace mapspace
{
    // 생성자 구현
    TerrainGenerator::TerrainGenerator()
    {
        std::ifstream terrainFile("Game/data/terrain.json");
        if (!terrainFile.is_open()) 
        {
            std::cout << "can't open file!" << std::endl;
            return;
        }

        json terrainData;
        terrainFile >> terrainData;

        t_steps = terrainData["setting"]["temp_steps"].get<std::vector<double>>();
        h_steps = terrainData["setting"]["humid_steps"].get<std::vector<double>>();
        matrix = terrainData["setting"]["matrix"].get<std::vector<std::vector<std::string>>>();
        e_matrix = terrainData["setting"]["matrix_enum"].get<std::vector<std::vector<int>>>();
    }

    // 인덱스 추출 로직
    int TerrainGenerator::GetIdxForMatrix(double envar, const std::vector<double>& steps)
    {
        auto it = std::lower_bound(steps.begin(), steps.end(), envar);
        int idx = std::distance(steps.begin(), it);
        return std::min((int)steps.size() - 1, idx);
    }

    // 지형 데이터 초기화 및 비트 연산 로직
    uint8_t TerrainGenerator::InitTerrainData(int width, int height, int x, int y, int d)
    {
        uint8_t tileTypeData;
        uint8_t tileHeightData;

        double nx = (double)x / width * d; 
        double ny = (double)y / height * d;

        // Noise 부여 (FBM)
        double h_val = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
        double t_val = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
        double humid = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);

        // 높이에 따른 온도 보정
        t_val = std::clamp(t_val - (h_val * 0.3), 0.0, 1.0);

        // 휘태커 도표 UI 출력 영역 예외 처리
        if (x < 100 && y < 100)
        {
            t_val = x / 100.0;
            humid = y / 100.0;
            h_val = 0.0;
        }

        // 행렬 인덱스 계산
        int h_idx = GetIdxForMatrix(humid, h_steps);
        int t_idx = GetIdxForMatrix(t_val, t_steps);

        // 높이값에 따른 타일 타입 및 높이 데이터 결정
        if (h_val < 0.3) 
        {
            tileTypeData = 0;
            tileHeightData = 0;
        }
        else if (h_val < 0.32) 
        {
            tileTypeData = 4;
            tileHeightData = 1;
        }
        else 
        {
            tileTypeData = (uint8_t)e_matrix[h_idx][t_idx];
            
            if (0.58 < h_val) tileHeightData = 3;
            else tileHeightData = 1;
        }

        // 비트 연산 후 반환
        return ((tileHeightData << HEIGHT_SHIFT) & HEIGHT_MASK) | (tileTypeData & TILE_TYPE_MASK);
    }

    // -------------------------------
    // Chunk 구조
    // -------------------------------
    Chunk::Chunk(int x, int y) : chunkX(x), chunkY(y), dirty(true)
    {
        terrain.resize(SIZE * SIZE);
        // dynamic.resize(SIZE * SIZE, 0); 아직 다이나믹한 요소 없음
    }
    
    // -------------------------------
    // Map 클래스 : 처음 딱 한번만 만들어짐
    // -------------------------------
    Map::Map(int w, int h) : width(w), height(h) // Map 클래스
    {
        chunkWidth  = (width  + Chunk::SIZE - 1) / Chunk::SIZE;
        chunkHeight = (height + Chunk::SIZE - 1) / Chunk::SIZE;
    
        chunks.reserve(chunkWidth * chunkHeight);
    
        for(int cy=0; cy<chunkHeight; ++cy)
            for(int cx=0; cx<chunkWidth; ++cx)
                chunks.emplace_back(cx, cy);

        TerrainGenerator TG;
        for(int y=0; y<height; ++y)
            for(int x=0; x<width; ++x)
                SetTileData(x,y,TG.InitTerrainData(width, height, x, y, 10));

        SmoothBiomes(5,2);
        GenerateBeaches();
    }

    // -------------------------------
    // Chunk / local 좌표 변환
    // -------------------------------
    Chunk& Map::GetChunk(int x, int y)
    {
        int safeX = std::clamp(x, 0, width - 1);
        int safeY = std::clamp(y, 0, height - 1);
        
        int cx = safeX / Chunk::SIZE;
        int cy = safeY / Chunk::SIZE;
        
        return chunks[cy * chunkWidth + cx];
    }
    const Chunk& Map::GetChunk(int x, int y) const 
    {
        int safeX = std::clamp(x, 0, width - 1);
        int safeY = std::clamp(y, 0, height - 1);
        
        int cx = safeX / Chunk::SIZE;
        int cy = safeY / Chunk::SIZE;
        
        return chunks[cy * chunkWidth + cx];
    }
    
    // -------------------------------
    // CanMove: height 규칙 적용
    // -------------------------------
    bool Map::CanMove(int fromX, int fromY, int toX, int toY) const
    {
        if(toX < 0 || toX >= width || toY < 0 || toY >= height)
            return false;
    
        const Chunk& toChunk = GetChunk(toX,toY);
        int idx = toChunk.Index(LocalX(toX), LocalY(toY));
    
        uint8_t fromHeight = GetHeight(fromX, fromY);
        uint8_t toHeight   = GetHeight(toX, toY);
    
        // 0 = 물
        if(fromHeight == 0 || toHeight == 0)
            return false;
    
        // 1 ↔ 3 직접 이동 불가
        if((fromHeight == 1 && toHeight == 3) || (fromHeight == 3 && toHeight == 1))
            return false;
    
        // 나머지는 이동 가능 (1↔2, 2↔3, 1↔1, 3↔3, 2↔2)
        return true;
    }

    // -------------------------------
    //  근처에 가장 많은 바이옴 검색
    // -------------------------------
    std::pair<uint8_t, int> Map::GetMostFrequentBiomeWithCount(int x, int y) const {
        // 인덱스: 바이옴 타입(TT), 값: 등장 횟수
        int counts[64] = { 0, }; // TT::MAX가 64이므로
        
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
    
                int nx = x + i;
                int ny = y + j;
                
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    uint8_t type = GetTileType(nx, ny);
                    counts[type]++;
                }
            }
        }
        
        uint8_t mostFrequent = 0;
        int maxCount = 0;
        for (uint8_t i = 0; i < 64; ++i) {
            if (counts[i] > maxCount) {
                maxCount = counts[i];
                mostFrequent = i;
            }
        }
        
        return { mostFrequent, maxCount };
    }

    // -------------------------------
    // 바이옴 다듬기
    // -------------------------------
    void Map::SmoothBiomes(int threshold, int iterations) 
    {
        std::vector<uint8_t> nextTypes(width * height);
    
        for (int iter = 0; iter < iterations; ++iter) {
            
            // OpenMP 지시어: 루프를 여러 스레드로 분할 실행
            // shared(nextTypes): 모든 스레드가 이 버퍼를 공유함
            // private(cx, cy, currentChunk, lx, ly...): 각 스레드가 개별 변수를 가짐
            #pragma omp parallel for collapse(2) schedule(dynamic)
            for (int cy = 0; cy < chunkHeight; ++cy) {
                for (int cx = 0; cx < chunkWidth; ++cx) {
                    
                    // 각 스레드는 자신이 담당한 청크만 처리
                    Chunk& currentChunk = chunks[cy * chunkWidth + cx];
                    int startX = cx * Chunk::SIZE;
                    int startY = cy * Chunk::SIZE;
    
                    for (int ly = 0; ly < Chunk::SIZE; ++ly) {
                        int gy = startY + ly;
                        if (gy >= height) continue;
    
                        for (int lx = 0; lx < Chunk::SIZE; ++lx) {
                            int gx = startX + lx;
                            if (gx >= width) continue;
    
                            auto [bestType, count] = GetMostFrequentBiomeWithCount(gx, gy);
                            uint8_t currentType = currentChunk.terrain[ly * Chunk::SIZE + lx] & TILE_TYPE_MASK;
                            
                            // nextTypes[index]에 쓰는 작업은 타일마다 위치가 다르므로 
                            // Race Condition(경합)이 발생하지 않아 안전함
                            nextTypes[gy * width + gx] = (count >= threshold) ? bestType : currentType;
                        }
                    }
                }
            }
    
            // 결과 일괄 적용 (이 루프도 병렬화 가능)
            #pragma omp parallel for
            for (int i = 0; i < (int)nextTypes.size(); ++i) {
                int y = i / width;
                int x = i % width;
                SetTileType(x, y, nextTypes[i]);
            }
        }
    }

    // -------------------------------
    // Extra layer
    // -------------------------------
    TileExtra* Map::GetExtra(int x, int y)
    {
        Chunk& chunk = GetChunk(x,y);
        int idx = chunk.Index(LocalX(x), LocalY(y));
        auto it = chunk.extras.find(idx);
        if(it == chunk.extras.end()) return nullptr;
        return &it->second;
    }
    
    void Map::SetExtra(const TileExtra& extra)
    {
        int x = extra.x;
        int y = extra.y;
        Chunk& chunk = GetChunk(x,y);
        int idx = chunk.Index(LocalX(x), LocalY(y));
        chunk.extras[idx] = extra;
        chunk.dirty = true;
    }
}
