#include "Map.h"

namespace mapspace
{
    // -------------------------------
    // Reading Json...
    // -------------------------------
    
    // 파일 가져오기
    std::ifstream terrainFile("Game/data/terrain.json");
    if (!terrainFile.is_open()){ std::cout << "can't open file!" << std::endl; }
    json terrainData;
    terrainFile >> terrainData;
    
    // 데이터 불러오기
    std::vector<double> t_steps = terrainData["setting"]["temp_steps"].get<std::vector<double>>();
    std::vector<double> h_steps = terrainData["setting"]["humid_steps"].get<std::vector<double>>();
    std::vector<std::vector<std::string>> matrix= terrainData["setting"]["matrix"].get<std::vector<std::vector<std::string>>>();
    std::vector<std::vector<std::string>> e_matrix= terrainData["setting"]["matrix_enum"].get<std::vector<std::vector<int>>>();

    // -------------------------------
    // Chunk 구조
    // -------------------------------
    Chunk::Chunk(int x, int y) : chunkX(x), chunkY(y), dirty(true)
    {
        terrain.resize(SIZE * SIZE);
        // dynamic.resize(SIZE * SIZE, 0); 아직 다이나믹한 요소 없음
    }
    
    // -------------------------------
    // Map 클래스
    // -------------------------------
    Map::Map(int w, int h) : width(w), height(h)
    {
        chunkWidth  = (width  + Chunk::SIZE - 1) / Chunk::SIZE;
        chunkHeight = (height + Chunk::SIZE - 1) / Chunk::SIZE;
    
        chunks.reserve(chunkWidth * chunkHeight);
    
        for(int cy=0; cy<chunkHeight; ++cy)
            for(int cx=0; cx<chunkWidth; ++cx)
                chunks.emplace_back(cx, cy);

        for(int y=0; y<height; ++y){
            for(int x=0; x<width; ++x) // 맵 기본 생성 알고리즘
            {
            
            
                // -------------------------------
                // Noise 부여
                // -------------------------------
                double nx = (double)x / width * 10;
                double ny = (double)y / height * 10;
            
                // Perlin(6, 0.5, 2) -> min = 0.02, MAX = 0.7, average = 0.26 graph = _/\__
                double height = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
                double temperature = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
                double humidity = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);
            
                // 높이에 따른 온도 변화
                double temperature = temperature - (height * 0.3); 
                double temperature = std::clamp(temperature, 0.0, 1.0);
            
            
                // -------------------------------
                // 타일 설정
                // -------------------------------
                // lower_bound를 이용해 인덱스 추출
                int t_idx = std::lower_bound(t_steps.begin(), t_steps.end(), temp) - t_steps.begin();
                int h_idx = std::lower_bound(h_steps.begin(), h_steps.end(), humid) - h_steps.begin();
                
                // 범위 초과 방지 
                t_idx = std::min((int)t_steps.size() - 1, t_idx);
                h_idx = std::min((int)h_steps.size() - 1, h_idx);
            
                // matrix배열에 따른 TerrainType 부여 -------------------------------- Layer 1
                SetTileType(StringToTT(matrix[h_idx][t_idx]));
                if (0.58 < height) SetHeight(x,y,3);
                else SetHeight(x,y,1);

                // 높이 낮으면 물 고정 ----------------------------------------------- layer 2
                if (height < 0.3) {
                    SetTileType(x,y,StringToTT("water"));
                    SetHeight(x,y,0);
                }

                // -------------------------------
                // 휘태커 도표 UI 출력
                // -------------------------------
                if (x < 100 && y < 100) 
                {
                    double nx = x / 100.0;
                    double ny = y / 100.0;
                    
                    // upper_bound를 이용해 인덱스 추출
                    int t_idx = std::lower_bound(t_steps.begin(), t_steps.end(), nx) - t_steps.begin();
                    int h_idx = std::lower_bound(h_steps.begin(), h_steps.end(), ny) - h_steps.begin();
                    
                    // 범위 초과 방지 
                    t_idx = std::min((int)t_steps.size() - 1, t_idx);
                    h_idx = std::min((int)h_steps.size() - 1, h_idx);
            
                    // matrix배열에 따른 tileType 부여 -------------------------------- Layer 3
                    SetTileType(x,y,StringToTT(e_matrix[h_idx][t_idx]));
                    SetHeight(x,y,0);
                }
            }
        }
    }
    
    // -------------------------------
    // Chunk / local 좌표 변환
    // -------------------------------
    Chunk& Map::GetChunk(int x, int y)
    {
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
    
        const Chunk& toChunk = const_cast<Map*>(this)->GetChunk(toX,toY);
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
