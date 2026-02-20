#include "world.h"

namespace worldspace{
    tile world[width][height]{};
    int worldInit() {

        
        PerlinNoiseSpace::PerlinNoise perlin(1024);

        std::vector<std::vector<double>> heightMap(width, std::vector<double>(height));

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
    
    tile water[width][height]{};
    int waterInit() {

        
        PerlinNoiseSpace::PerlinNoise perlin(1024);

        std::vector<std::vector<double>> heightMap(width, std::vector<double>(height));

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                double nx = (double)x / width;
                double ny = (double)y / height;

                water[x][y].dst = {x, y, 1, 1};

                double watered = PerlinNoiseSpace::fbm(perlin, nx, ny, 4, 0.7, 2, 1, 6);
                if (0.6 < watered){
                    water[x][y].bright = watered * watered * watered * watered * 400;
                }else{
                    water[x][y].bright = 0.0;
                }
            }
        }
        

        return 0;
    }
}