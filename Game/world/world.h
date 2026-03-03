#pragma once

#include "../../Engine/GameManager/GameManager.h"
#include <random>
#include <stdio.h>


// const double p[101] = { // 정규분포표에서 각 누적확률을 나타내는 숫자표
//     0,
//     0.0099, 0.0202, 0.0301, 0.0401, 0.0500, 0.0594, 0.0694, 0.0793, 0.0892, 0.0990, 
//     0.1093, 0.1190, 0.1270, 0.1416, 0.1492, 0.1587, 0.1660, 0.1717, 0.1772, 0.2005, 
//     0.2113, 0.2143, 0.2287, 0.2407, 0.2498, 0.2632, 0.2687, 0.2743, 0.2795, 0.2843, 
//     0.2897, 0.2962, 0.3032, 0.3089, 0.3183, 0.3251, 0.3328, 0.3400, 0.3466, 0.3520, 
//     0.3595, 0.3663, 0.3730, 0.3762, 0.3836, 0.3910, 0.3943, 0.4013, 0.4082, 0.5, 
//     0.5918, 0.5973, 0.6032, 0.6083, 0.6145, 0.6206, 0.6255, 0.6320, 0.6382, 0.6450, 
//     0.6495, 0.6562, 0.6633, 0.6701, 0.6769, 0.6867, 0.6929, 0.7017, 0.7088, 0.7152, 
//     0.7216, 0.7281, 0.7383, 0.7479, 0.7557, 0.7642, 0.7734, 0.7923, 0.7964, 0.8043, 
//     0.8245, 0.8290, 0.8373, 0.8563, 0.8684, 0.8804, 0.8888, 0.9000, 0.9105, 0.9192, 
//     0.9272, 0.9350, 0.9409, 0.9500, 0.9599, 0.9697, 0.9798, 0.9901, 0.9901, 0.9990
// };

namespace worldspace{

    const int width = 1280;
    const int height = 720;


    int worldInit();
    int waterInit();

    struct tile{
        double height;
        double temperature;
        double humidity;
        std::array<int,4> color;
        std::string tileType;
        SDL_Rect dst;
    };

    extern tile world[width][height];
    extern tile water[width][height];
}

namespace PerlinNoiseSpace{
    class PerlinNoise {
    private:
        std::vector<int> p;

        double fade(double t) const {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        double lerp(double a, double b, double t) const {
            return a + t * (b - a);
        }

        double grad(int hash, double x, double y) const {
            int h = hash & 7; // 8 directions
            double u = h < 4 ? x : y;
            double v = h < 4 ? y : x;
            return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
        }

    public:
        PerlinNoise(unsigned int seed = 1024) {
            p.resize(256);
            std::iota(p.begin(), p.end(), 0);
            std::default_random_engine engine(seed);
            std::shuffle(p.begin(), p.end(), engine);
            p.insert(p.end(), p.begin(), p.end());
        }

        double noise(double x, double y) const {
            int xi = (int)floor(x) & 255;
            int yi = (int)floor(y) & 255;

            double xf = x - floor(x);
            double yf = y - floor(y);

            double u = fade(xf);
            double v = fade(yf);

            int aa = p[p[xi] + yi];
            int ab = p[p[xi] + yi + 1];
            int ba = p[p[xi + 1] + yi];
            int bb = p[p[xi + 1] + yi + 1];

            double x1 = lerp(grad(aa, xf, yf),
                            grad(ba, xf - 1, yf), u);

            double x2 = lerp(grad(ab, xf, yf - 1),
                            grad(bb, xf - 1, yf - 1), u);


            return (lerp(x1, x2, v) + 1.0) / 2.0; // 0~1 정규화
        }
    };
    double fbm(const PerlinNoise& perlin, double x, double y, int octaves, double persistence, double lacunarity, double amplitude = 1.0, double frequency = 1.0);
}
