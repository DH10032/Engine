#include "world.h"

namespace PerlinNoiseSpace{


    double fbm(const PerlinNoise& perlin, double x, double y, int octaves, double persistence, double lacunarity, double amplitude = 1.0, double frequency = 1.0)
    {
        double total = 0.0;
        double maxValue = 0.0;

        for (int i = 0; i < octaves; i++) {
            total += perlin.noise(x * frequency, y * frequency) * amplitude;
            maxValue += amplitude;

            amplitude *= persistence;
            frequency *= lacunarity;
        }

        return total / maxValue;
    }

}
