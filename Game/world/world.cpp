#include "world.h"


namespace worldspace{


    int SEED = 1024;
    tile world[width][height]{};
    int worldInit() {

        std::ifstream file("Game/data/terrain.json");
        if (!file.is_open()){
            std::cout << "can't open file!" << std::endl;
        }
        json j;
        file >> j;

        
        PerlinNoiseSpace::PerlinNoise perlin1(SEED);
        PerlinNoiseSpace::PerlinNoise perlin2(SEED+1);
        PerlinNoiseSpace::PerlinNoise perlin3(SEED+2);

        for (int x = 0; x < width; x++) { // 펄린 변수 부여, 기본값 초기화
            for (int y = 0; y < height; y++) {
                double nx = (double)x / width;
                double ny = (double)y / height;
                world[x][y].dst = {x, y, 1, 1};
                world[x][y].height = PerlinNoiseSpace::fbm(perlin1, nx, ny, 6, 0.5, 2); // 6,0.5,2 -> min = 8, MAX = 40, average = 22
                world[x][y].temperature = PerlinNoiseSpace::fbm(perlin1, nx, ny, 6, 0.5, 3);
                world[x][y].humidity = PerlinNoiseSpace::fbm(perlin1, nx, ny, 6, 0.4, 3);

                world[x][y].height = (world[x][y].height * world[x][y].height) * 100.0; // 0 ~ 100
                world[x][y].temperature = (world[x][y].temperature * world[x][y].temperature) * 60.0 - 20.0; // -20 ~ 40
                world[x][y].humidity = (world[x][y].humidity * world[x][y].humidity) * 200.0 - 100.0; // -100 ~ 100

                world[x][y].tileType = "plain";
                world[x][y].color = {0,255,0,255};
            }
        }

        double mh = 22;
        double Mh = 22;
        int totalh = 0;
        int num = 0;
        for (int x = 0; x < width; x++) { // test
            for (int y = 0; y < height; y++) {
                if (world[x][y].height < mh) mh = world[x][y].height;
                if (world[x][y].height > Mh) Mh = world[x][y].height;
                totalh += world[x][y].height;
                num++;
            }
        }
        std::cout << mh << std::endl;
        std::cout << Mh << std::endl;
        std::cout << totalh << std::endl;
        std::cout << num << std::endl;
        std::cout << (totalh / num) << std::endl;

        for (int x = 0; x < width; x++) { // 타일 설정
            for (int y = 0; y < height; y++) {
                double h = world[x][y].height;
                double temp = world[x][y].temperature;
                double hum = world[x][y].humidity;
                std::string& t = world[x][y].tileType;
                if (54 < h){           // 산
                    if (temp < 10){
                        t = "ice";
                    }else if(57.5 < h){
                        t = "water";
                    }else{
                        t = "mountain";
                    }
                }
                else if (36.3 < h <= 54){  // 평지
                    if (10 < temp){
                        if      (20 < hum)  t = "jungle";
                        else if (hum < 0)   t = "dessert";
                        else                t = "savanna";
                    }
                }
                else{                      // 바다
                    if (h < 35) t = "water";
                    else        t = "sand";
                }
            }
        }        
        
        for (int x = 0; x < width; x++) { // 색 지정
            for (int y = 0; y < height; y++) {
                std::string type = world[x][y].tileType;
                auto colorJson = j[type];  // JSON에서 배열 가져오기

                for (int i = 0; i < 4; i++) {
                    world[x][y].color[i] = colorJson[i];
                }           
            }
        }



        

        return 0;
    }
/*
    ## 바이옴 변수
        높이
        온도
        습도

    ## 바이옴 리스트

    - 산
        - 높이 높음

    - 고산호수
        - 높이 매우 높음
        - 습기 매우 높음

    - 바다
        - 높이 낮음
        - 습기 매우 높음

    - 숲
        - 온도 중간
        - 습기 중간

    - 사막
        - 온도 높음
        - 습기 낮음

    - 정글
        - 온도 높음
        - 습기 높음

    - 사바나
        - 온도 높음
        - 습기 중간

    - 타이가
        - 온도 낮음
        - 습기 낮음

    - 툰드라
        - 온도 매우 낮음
.                           */
}