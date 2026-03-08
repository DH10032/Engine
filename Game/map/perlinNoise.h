#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <cmath>

namespace PerlinNoiseSpace {

class PerlinNoise
{
private:
    std::vector<int> p;

    double fade(double t) const;
    double lerp(double a, double b, double t) const;
    double grad(int hash, double x, double y) const;

public:
    PerlinNoise(unsigned int seed = 1024);

    double noise(double x, double y) const;
};

// fbm 함수 선언
double fbm(const PerlinNoise& perlin, double x, double y, int octaves, double persistence, double lacunarity, double amplitude = 1.0, double frequency = 1.0);

} // namespace PerlinNoiseSpace
