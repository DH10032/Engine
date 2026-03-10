#pragma once

#include "../../Engine/GameManager/GameManager.h"
#include "perlinNoise.h"
#include <random>
#include <stdio.h>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <omp.h>

namespace mapspace
{

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

// -------------------------------
// 비트 마스크 정의
// -------------------------------
constexpr uint8_t TILE_TYPE_MASK = 0b00111111; // bit0~5
constexpr uint8_t HEIGHT_MASK    = 0b11000000; // bit6~7
constexpr uint8_t HEIGHT_SHIFT   = 6;

// -------------------------------
// TerrainType & Extra
// -------------------------------
enum class TT : uint8_t // TerrainType
{
    water = 0,
    plain,
    forest,
    jungle,
    dessert,
    savanna,
    taiga,
    meadow,
    tundra,
    karst,
    swamp,
    iced_plain,
    iced_karst,
    snow,
    glacier,
    volcano,
    // ... 최대 64종류
    MAX = 64
};

constexpr const char* TTStrings[] = {
    "water", "plain", "forest", "jungle", "dessert", "savanna", "taiga", "meadow", "tundra", "karst", "swamp", "iced_plain", "iced_karst", "snow", "glacier", "volcano"
};

inline TT StringToTT(const std::string& str)
{
    if (str == "water")  	 return TT::water;
    if (str == "plain")  	 return TT::plain;
    if (str == "forest")   	 return TT::forest;
    if (str == "jungle")   	 return TT::jungle;
    if (str == "dessert") 	 return TT::dessert;
    if (str == "savanna")    return TT::savanna;
    if (str == "taiga") 	 return TT::taiga;
    if (str == "meadow") 	 return TT::meadow;
    if (str == "tundra") 	 return TT::tundra;
    if (str == "karst") 	 return TT::karst;
    if (str == "swamp") 	 return TT::swamp;
    if (str == "iced_plain") return TT::iced_plain;
    if (str == "iced_karst") return TT::iced_karst;
    if (str == "snow") 		 return TT::snow;
    if (str == "glacier") 	 return TT::glacier;
    if (str == "volcano") 	 return TT::volcano;

    return TT::water; // 기본값
}

inline const char* TTToString(TT b) { return TTStrings[static_cast<uint8_t>(b)]; }

struct ResourceStack
{
    DropType type;
    uint16_t amount;
};

struct TileExtra
{
    uint16_t hp;
    std::vector<ResourceStack> resources; // 여러 종류 표현 위해
    uint8_t owner;
    DropType drop;
    bool isBlocked;
};

// -------------------------------
// TerrainGenerator 클래스
// -------------------------------
class TerrainGenerator {
private:
	// -------------------------------
	// 시드 설정 (임시)
	// -------------------------------
	int SEED = 1024;
	PerlinNoiseSpace::PerlinNoise perlin1(SEED);
	PerlinNoiseSpace::PerlinNoise perlin2(SEED+1);
	PerlinNoiseSpace::PerlinNoise perlin3(SEED+2);

    std::vector<double> t_steps;
    std::vector<double> h_steps;
    std::vector<std::vector<std::string>> matrix;
    std::vector<std::vector<int>> e_matrix;

    // 내부 유틸리티 함수
    int GetIdxForMatrix(double envar, const std::vector<double>& steps);

public:
    // 생성자
    TerrainGenerator();

    // 지형 데이터 초기화 함수
    uint8_t InitTerrainData(int width, int height, int x, int y, int d);
};

// -------------------------------
// Chunk 구조
// -------------------------------
struct Chunk
{
    static constexpr int SIZE = 32;

    int chunkX;
    int chunkY;

    std::vector<uint8_t> terrain;
    // std::vector<uint8_t> dynamic; : 아직은 맵에 다이나믹한 요소가 없음
    std::unordered_map<int, TileExtra> extras;

    bool dirty;

    Chunk(int x = 0, int y = 0);

    inline int Chunk::Index(int x, int y) const { return y * SIZE + x; }
};

// -------------------------------
// Map 클래스
// -------------------------------
class Map
{
private:
    int width;
    int height;
    int chunkWidth;
    int chunkHeight;

    std::vector<Chunk> chunks;

    std::pair<uint8_t, int> GetMostFrequentBiomeWithCount(int x, int y) const;
    std::vector<uint8_t> GetFullTileTypeBuffer() const;
	bool IsAdjacentToWater(int x, int y) const;

public:
    Map(int w, int h);

    Chunk& GetChunk(int x, int y);
	const Chunk& GetChunk(int x, int y) const;

	inline int LocalX(int x) const { return x % Chunk::SIZE; }
	inline int LocalY(int y) const { return y % Chunk::SIZE; }

	// Terrain
	inline uint8_t GetTileData(int x, int y) const
	{
		const Chunk& chunk = GetChunk(x,y);
		return chunk.terrain[chunk.Index(LocalX(x), LocalY(y))];
	}
	inline void SetTileData(int x, int y, uint8_t data)
	{
		Chunk& chunk = GetChunk(x,y);
		int idx = chunk.Index(LocalX(x), LocalY(y));
		chunk.terrain[idx] = data;
		chunk.dirty = true;
	}
	
	inline uint8_t GetHeight(int x, int y) const { return (GetTileData(x,y) & HEIGHT_MASK) >> HEIGHT_SHIFT; } // 0 ~ 3
	inline void SetHeight(int x, int y, uint8_t h)
	{
		h = std::min<uint8_t>(h, 3);
		Chunk& chunk = GetChunk(x,y);
		int idx = chunk.Index(LocalX(x), LocalY(y));
		chunk.terrain[idx] = (chunk.terrain[idx] & ~HEIGHT_MASK) | ((h << HEIGHT_SHIFT) & HEIGHT_MASK);
		chunk.dirty = true;
	}

	inline uint8_t GetTileType(int x, int y) const { return GetTileData(x,y) & TILE_TYPE_MASK; }
	inline void SetTileType(int x, int y, uint8_t type)
	{
		Chunk& chunk = GetChunk(x,y);
		int idx = chunk.Index(LocalX(x), LocalY(y));
		chunk.terrain[idx] = (chunk.terrain[idx] & ~TILE_TYPE_MASK) | (type & TILE_TYPE_MASK);
		chunk.dirty = true;
	}

    // SmoothBiomes
	void SmoothBiomes(int threshold = 5, int iterations = 2);

    // CanMove
    bool CanMove(int fromX, int fromY, int toX, int toY) const;

    // Extra
    TileExtra* GetExtra(int x, int y);
    void SetExtra(int x, int y, const TileExtra& extra);
};

}
