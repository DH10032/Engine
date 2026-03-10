#include "Map.h"

struct TileEnvironments {
    double height;
    double temp;
    double humid;
}

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


    void InitTile(int x, int y)  // 맵 기본 생성 알고리즘
    {
        TileEnvironments TE;

        TE = SetNoise(x,y,10,TE);
        
        if (x < 100 && y < 100)
            TE = PrintWhittaker(TE);

        RefineHeight(TE.height);

        h_idx = GetIdxForMatrix(TE.humid, h_steps);
        t_idx = GetIdxForMatrix(TE.temp, t_steps);

        // matrix배열에 따른 tileType 부여
        if (TE.height < 0.3) SetTileType(x,y,0);
        else SetTileType(x,y,e_matrix[h_idx][t_idx]);
    }

    TileEnvironments SetNoise(int x, int y, int Density, TileEnvironments TE) // Noise 부여
    {
        double nx = (double)x / width * Density;
        double ny = (double)y / height * Density;
    
        // Perlin(6, 0.5, 2) -> min = 0.02, MAX = 0.7, average = 0.26 graph = _/\__
        double TE.height = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
        double TE.temperature = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
        double TE.humidity = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);
    
        // 높이에 따른 온도 변화
        double TE.temperature = TE.temperature - (TE.height * 0.3); 
        double TE.temperature = std::clamp(TE.temperature, 0.0, 1.0);

        return TE;
    }

    int GetIdxForMatrix(double envar std::vector<double> steps) // Matrix 인덱스 추출
    {
        int idx = std::lower_bound(steps.begin(), steps.end(), envar) - steps.begin(); // lower_bound를 이용해 인덱스 추출
        return std::min((int)steps.size() - 1, idx); // 범위 초과 방지
    }

    TileEnvironments PrintWhittaker(TileEnvironments TE) // 휘태커 도표 UI 출력
    {
        double TE.temperature = x / 100.0;
        double TE.humidity = y / 100.0;
        double TE.height = 0.0;
        return TE;
    }

    void RefineHeight(TileEnvironments TE)
    {
        if (height < 0.3) SetHeight(x,y,0);
        else if (0.58 < height) SetHeight(x,y,3);
        else SetHeight(x,y,1);
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

        for(int y=0; y<height; ++y)
            for(int x=0; x<width; ++x)
                InitTile(x,y);
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
