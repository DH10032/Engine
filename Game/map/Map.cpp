#include "Map.h"

namespace mapspace
{
    class TerrainGenerator {
    private:
        std::vector<double> t_steps;
        std::vector<double> h_steps;
        std::vector<std::vector<std::string>> matrix;
        std::vector<std::vector<int>> e_matrix;

        int GetIdxForMatrix(double envar std::vector<double> steps) // Matrix 인덱스 추출
        {
            int idx = std::lower_bound(steps.begin(), steps.end(), envar) - steps.begin(); // lower_bound를 이용해 인덱스 추출
            return std::min((int)steps.size() - 1, idx); // 범위 초과 방지
        }
    public:
        void TerrainGenerator() // Reading Json...
        {
            // 파일 가져오기
            std::ifstream terrainFile("Game/data/terrain.json");
            if (!terrainFile.is_open()) std::cout << "can't open file!" << std::endl;
            json terrainData;
            terrainFile >> terrainData;
            
            // 데이터 불러오기
            this->t_steps = terrainData["setting"]["temp_steps"].get<std::vector<double>>();
            this->h_steps = terrainData["setting"]["humid_steps"].get<std::vector<double>>();
            this->matrix= terrainData["setting"]["matrix"].get<std::vector<std::vector<std::string>>>();
            this->e_matrix = terrainData["setting"]["matrix_enum"].get<std::vector<std::vector<uint8_t>>>();
        }

        uint8_t InitTerrainData(int x, int y, int d) : x(x), y(y), Density(d)
        {
            uint8_t tileTypeData;
            uint8_t tileHeightData;

            double nx = (double)x / width * Density;
            double ny = (double)y / height * Density;
    
            // Noise 부여
            // Perlin(6, 0.5, 2) -> min = 0.02, MAX = 0.7, average = 0.26 graph = _/\__
            double height = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
            double temp = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
            double humid = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);
        
            // 높이에 따른 온도 변화
            temp = temp - (height * 0.3); 
            temp = std::clamp(temp, 0.0, 1.0);
    
            if (x < 100 && y < 100) // 휘태커 도표 UI 출력
            {
                temp = x / 100.0;
                humid = y / 100.0;
                height = 0.0;
            }

            // temp, humid의 step 계산
            int h_idx = this->GetIdxForMatrix(humid, this->h_steps);
            int t_idx = this->GetIdxForMatrix(temp, this->t_steps);

            // TileType 계산
            if (height < 0.3) tileTypeData = 0;
            else tileTypeData = this.e_matrix[h_idx][t_idx];

            // TileHeight 계산
            if (height < 0.3) tileHeightData = 0;
            else if (0.58 < height) tileHeightData = 3;
            else tileHeightData = 1;

            return ((tileHeightData << HEIGHT_SHIFT) & HEIGHT_MASK) | (tileTypeData & TILE_TYPE_MASK);
        }
    }

    Chunk::Chunk(int x, int y) : chunkX(x), chunkY(y), dirty(true) // Chunk 구조
    {
        terrain.resize(SIZE * SIZE);
        // dynamic.resize(SIZE * SIZE, 0); 아직 다이나믹한 요소 없음
    }
    
    // -------------------------------
    // Map 클래스
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
                SetTileData(x,y,TG.InitTerrainData(x,y,10));
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
