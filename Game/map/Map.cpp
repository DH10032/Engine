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
        double c_val = PerlinNoiseSpace::fbm(perlin4, nx, ny, 3, 0.5, 1.5) * 2.0 - 1.2;
        double h_val = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
        double t_val = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
        double humid = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);

        // 대륙성에 따른 높이 보정
        h_val = std::clamp(h_val + c_val, 0.0, 1.0);

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
        assert(0<=x && 0<=y && x<width && y<height);
        
        int cx = x / Chunk::SIZE;
        int cy = y / Chunk::SIZE;
        
        return chunks[cy * chunkWidth + cx];
    }
    const Chunk& Map::GetChunk(int x, int y) const 
    {
        assert(0<=x && 0<=y && x<width && y<height);
        
        int cx = x / Chunk::SIZE;
        int cy = y / Chunk::SIZE;
        
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
    // 바이옴 다듬기
    // -------------------------------
    void Map::SmoothBiomes(int threshold, int iterations) 
    {
        // 초기 flat buffer 생성
        std::vector<uint8_t> tileTypes(width * height);
        for(int y=0; y<height; ++y)
            for(int x=0; x<width; ++x)
                tileTypes[y*width + x] = GetTileType(x, y);
    
        std::vector<uint8_t> nextTileTypes = tileTypes;
    
        for(int iter = 0; iter < iterations; ++iter) 
        {
            // -----------------------
            // smoothing kernel 적용
            // -----------------------
            #pragma omp parallel for collapse(2) schedule(dynamic)
            for(int y = 0; y < height; ++y) {
                for(int x = 0; x < width; ++x) {
                    int counts[64] = {0};
                    // 5x5 neighborhood
                    for(int dy = -2; dy <= 2; ++dy) {
                        for(int dx = -2; dx <= 2; ++dx) {
                            int nx = x + dx;
                            int ny = y + dy;
                            if(nx < 0 || nx >= width || ny < 0 || ny >= height) continue;
                            counts[tileTypes[ny * width + nx]]++;
                        }
                    }
    
                    // 가장 많이 나온 tile type
                    uint8_t bestType = 0;
                    int maxCount = 0;
                    for(int i = 0; i < 64; ++i) {
                        if(counts[i] > maxCount) {
                            maxCount = counts[i];
                            bestType = static_cast<uint8_t>(i);
                        }
                    }
                    // threshold 적용
                    nextTileTypes[y * width + x] = (maxCount >= threshold) ? bestType : tileTypes[y * width + x];
                }
            }
            // 다음 iteration을 위해 swap
            std::swap(tileTypes, nextTileTypes);
        }
        // -----------------------
        // 결과 반영
        // -----------------------
        #pragma omp parallel for collapse(2) schedule(static)
        for(int y = 0; y < height; ++y){
            for(int x = 0; x < width; ++x){
                SetTileType(x, y, tileTypes[y * width + x]);
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
    
    void Map::SetExtra(int x, int y, const TileExtra& extra)
    {
        Chunk& chunk = GetChunk(x,y);
        int idx = chunk.Index(LocalX(x), LocalY(y));
        chunk.extras[idx] = extra;
        chunk.dirty = true;
    }
}
