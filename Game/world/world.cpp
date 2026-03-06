#include "world.h"

namespace worldspace
{
    // ===============================
    // Reading Json...
    // ===============================

    // 파일 가져오기
    std::ifstream terrainFile("Game/data/terrain.json");
    if (!terrainFile.is_open()){ std::cout << "can't open file!" << std::endl; }
    json terrainData;
    terrainFile >> terrainData;

    // 데이터 불러오기
    std::vector<double> t_steps = terrainData["setting"]["temp_steps"].get<std::vector<double>>();
    std::vector<double> h_steps = terrainData["setting"]["humid_steps"].get<std::vector<double>>();
    std::vector<std::vector<std::string>> matrix= terrainData["setting"]["matrix"].get<std::vector<std::vector<std::string>>>();

    // 시드 설정
    int SEED = 1024;
    PerlinNoiseSpace::PerlinNoise perlin1(SEED);
    PerlinNoiseSpace::PerlinNoise perlin2(SEED+1);
    PerlinNoiseSpace::PerlinNoise perlin3(SEED+2);


    TerrainType initByChunk(int x, int y) 
    {

        // ===================================
        // 휘태커 도표 UI 출력
        // ===================================
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


            // matrix배열에 따른 tileType 부여
            return terrainMap[matrix[h_idx][t_idx]];
        }


        // ===================================
        // Noise 부여
        // ===================================

        x /= 16;
        y /= 16;
        double nx = (double)x / width * 10;
        double ny = (double)y / height * 10;

        // Perlin(6, 0.5, 2) -> min = 0.02, MAX = 0.7, average = 0.26 graph = _/\_
        double height = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
        double temperature = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
        double humidity = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);

        // 높이에 따른 온도 변화
        double temperature = temperature - (height * 0.3); 
        double temperature = std::clamp(temperature, 0.0, 1.0);


        // ====================================
        // 타일 설정
        // ====================================

        // 높이 낮으면 물 고정
        if (height < 0.3) world[x][y].tileType = terrainMap["water"];

        // lower_bound를 이용해 인덱스 추출
        int t_idx = std::lower_bound(t_steps.begin(), t_steps.end(), temp) - t_steps.begin();
        int h_idx = std::lower_bound(h_steps.begin(), h_steps.end(), humid) - h_steps.begin();
        
        // 범위 초과 방지 
        t_idx = std::min((int)t_steps.size() - 1, t_idx);
        h_idx = std::min((int)h_steps.size() - 1, h_idx);

        // matrix배열에 따른 TerrainType 부여
        return terrainMap[matrix[h_idx][t_idx]];
        
        // JSON에서 배열 통한 색 지정
        /*
        std::string type = world[x][y].tileType; // 이름 단축 + type오류 방지
        auto colorJson = terrainData["color"][type];

        for (int i = 0; i < 4; i++) { world[x][y].color[i] = colorJson[i]; }
        if (0.6 < height) world[x][y].color[3] = 200;
                                                            */
    }
}
