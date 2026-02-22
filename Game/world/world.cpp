#include "world.h"

namespace worldspace{
    tile world[width][height]{};
    int worldInit() {

        
        PerlinNoiseSpace::PerlinNoise perlin(1024);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                double nx = (double)x / width;
                double ny = (double)y / height;
                world[x][y].dst = {x, y, 1, 1};
                world[x][y].bright = PerlinNoiseSpace::fbm(perlin, nx, ny, 6, 0.4, 3) * 255.0;
            }
        }
        

        return 0;
    }
/*
    ## 바이옴 변수
        높이
        습기
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