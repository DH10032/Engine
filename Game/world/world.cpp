#include "world.h"

namespace worldspace{
    tile world[width][height]{};
    int worldInit() {

        PerlinNoiseSpace::PerlinNoise perlin(1024);

        std::vector<std::vector<double>> heightMap(width,
            std::vector<double>(height));

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                double nx = x / 100;
                double ny = y / 100;
        
                world[x][y].dst = {x*3,y*3,3,3};
                world[x][y].bright = PerlinNoiseSpace::fbm(perlin, nx, ny, 6, 0.5, 2.0);
                std::cout << world[x][y].bright;
            }
            std::cout << std::endl;
        }
        

        return 0;
    }
    tile& GetTile(int x, int y){
        return world[x][y];
    }
}