#include "PerlinNoise.h"

namespace PerlinNoiseSpace {

// ----------------------
// PerlinNoise 구현
// ----------------------
PerlinNoise::PerlinNoise(unsigned int seed)
{
    if(seed == 1024)
    {
        std::random_device rd;
        std::mt19937::result_type seed = rd();
        unsigned int seed = seed_dist(temp);
    }
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    std::mt19937 engine(seed);
    std::shuffle(p.begin(), p.end(), engine);
    p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::fade(double t) const
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double a, double b, double t) const
{
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y) const
{
    int h = hash & 7; // 8 directions
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

double PerlinNoise::noise(double x, double y) const
{
    int xi = (int)std::floor(x) & 255;
    int yi = (int)std::floor(y) & 255;

    double xf = x - std::floor(x);
    double yf = y - std::floor(y);

    double u = fade(xf);
    double v = fade(yf);

    int aa = p[p[xi] + yi];
    int ab = p[p[xi] + yi + 1];
    int ba = p[p[xi + 1] + yi];
    int bb = p[p[xi + 1] + yi + 1];

    double x1 = lerp(grad(aa, xf, yf), grad(ba, xf - 1, yf), u);
    double x2 = lerp(grad(ab, xf, yf - 1), grad(bb, xf - 1, yf - 1), u);

    return (lerp(x1, x2, v) + 1.0) / 2.0; // 0~1 정규화
}

// ----------------------
// FBM 구현
// ----------------------
double fbm(const PerlinNoise& perlin, double x, double y, int octaves, double persistence, double lacunarity, double amplitude, double frequency)
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

} // namespace PerlinNoiseSpace
