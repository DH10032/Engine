#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <numeric>
#include <random>
#include <cmath>
#include <algorithm>
#include <stdio.h>


namespace worldspace{

    const int width = 1280;
    const int height = 720;


    int worldInit();
    int waterInit();

    typedef struct{
            double bright;
            SDL_Rect dst;
        }tile;

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
