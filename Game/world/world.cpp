#include "world.h"


namespace worldspace{

    std::vector<double> t_steps;
    std::vector<double> h_steps;
    std::vector<std::vector<std::string>> matrix;

    int SEED = 1024;
    tile world[width][height]{};
    int worldInit() {

        std::ifstream terrainFile("Game/data/terrain.json");
        if (!terrainFile.is_open()){
            std::cout << "can't open file!" << std::endl;
        }
        json terrainData;
        terrainFile >> terrainData;

        t_steps = terrainData["setting"]["temp_steps"].get<std::vector<double>>();
        h_steps = terrainData["setting"]["humid_steps"].get<std::vector<double>>();
        matrix = terrainData["setting"]["matrix"].get<std::vector<std::vector<std::string>>>();

        
        PerlinNoiseSpace::PerlinNoise perlin1(SEED);
        PerlinNoiseSpace::PerlinNoise perlin2(SEED+1);
        PerlinNoiseSpace::PerlinNoise perlin3(SEED+2);

        for (int x = 0; x < width; x++) { // 펄린 변수 부여, 기본값 초기화
            for (int y = 0; y < height; y++) {
                double nx = (double)x / width * 10;
                double ny = (double)y / height * 10;
                world[x][y].dst = {x, y, 1, 1};
                //Perlin(6, 0.5, 2) -> min = 0.02, MAX = 0.7, average = 0.26 graph = _/\_
                world[x][y].height = PerlinNoiseSpace::fbm(perlin1, nx, ny, 4, 0.5, 2);
                world[x][y].temperature = PerlinNoiseSpace::fbm(perlin2, nx, ny, 4, 0.5, 3);
                world[x][y].humidity = PerlinNoiseSpace::fbm(perlin3, nx, ny, 4, 0.4, 3);
                
                world[x][y].temperature = world[x][y].temperature - (world[x][y].height * 0.3); 
                world[x][y].temperature = std::clamp(world[x][y].temperature, 0.0, 1.0);

                world[x][y].tileType = "plain";
                world[x][y].color = {0,255,0,255};
            }
        }

        for (int x = 0; x < width; x++) { // 타일 설정
            for (int y = 0; y < height; y++) {
                // 변수 이름들 단축
                double height = world[x][y].height;
                double temp = world[x][y].temperature;
                double humid = world[x][y].humidity;

                // upper_bound를 이용해 인덱스 추출
                int t_idx = std::lower_bound(t_steps.begin(), t_steps.end(), temp) - t_steps.begin();
                int h_idx = std::lower_bound(h_steps.begin(), h_steps.end(), humid) - h_steps.begin();
                
                // 범위 초과 방지 
                t_idx = std::min((int)t_steps.size() - 1, t_idx);
                h_idx = std::min((int)h_steps.size() - 1, h_idx);

                // matrix배열에 따른 tileType 부여
                world[x][y].tileType = matrix[h_idx][t_idx];
                if (height < 0.3) world[x][y].tileType = "water";
                
                // JSON에서 배열 통한 색 지정
                std::string type = world[x][y].tileType; // 이름 단축 + type오류 방지
                auto colorJson = terrainData["color"][type];

                for (int i = 0; i < 4; i++) {
                    world[x][y].color[i] = colorJson[i]; 
                }
                if (0.6 < height) world[x][y].color[3] = 200;
            }
        }        

        for (int x = 0; x < 100; x++) { // 휘태커 도표 UI로 출력
            for (int y = 0; y < 100; y++) {
                double nx = x / 100.0; 
                double ny = y / 100.0; 
                
                // upper_bound를 이용해 인덱스 추출
                int t_idx2 = std::lower_bound(t_steps.begin(), t_steps.end(), nx) - t_steps.begin();
                int h_idx2 = std::lower_bound(h_steps.begin(), h_steps.end(), ny) - h_steps.begin();
                
                // 범위 초과 방지 
                t_idx2 = std::min((int)t_steps.size() - 1, t_idx2);
                h_idx2 = std::min((int)h_steps.size() - 1, h_idx2);


                // matrix배열에 따른 tileType 부여
                world[x][y].tileType = matrix[h_idx2][t_idx2];

                // JSON에서 배열 통한 색 지정
                std::string type = world[x][y].tileType; // 이름 단축 + type오류 방지
                auto colorJson = terrainData["color"][type];

                for (int i = 0; i < 4; i++) {
                    world[x][y].color[i] = colorJson[i]; 
                }
            }
        }

        return 0;
    }
}
