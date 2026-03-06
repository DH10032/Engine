#pragma once

#include "../../Engine/GameManager/GameManager.h"
#include "perlinNoise.h"
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

    enum TileType : uint8_t {
        water,
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
        volcano
    };

    enum TILE_FLAGS : uint8_t {
        TILE_TYPE     = 0x0F, // 0000 1111 : 지형 정보
        TILE_EX       = 0x30, // 0011 0000 : 타일의 자원 종류 (0 : 없음 / 1 : 시야 보임 / 2 : 시야 차단 3 : 길 차단)
        TILE_WALKABLE = 0x40, // 0100 0000 : 지형 이동 가능 유무
        TILE_HEIGHT   = 0x80, // 1000 0000 : 지형 높이
    };
    /*
        비트 5 (Height),    비트 4 (Walkable),  지형 의미,              게임 내 역할
        0 (Low) ,           0 (No) ,           물 (Water),             저지대 장애물, 이동 불가
        0 (Low) ,           1 (Yes),           평지 (Ground),          일반적인 저지대 이동 구역
        1 (High),           1 (Yes),           언덕 (Slope),           저지대 ↔ 고지대 연결 통로
        1 (High),           0 (No) ,           고지대 (Cliff/High),    고지대 본토 (저지대 유닛 진입 불가)
    .                                                                                                      */

    enum EX_TYPE : uint8_t {
        EX_OWNER    = 0x0f // 0000 1111 : 15개 팀 -> 0 : 중립
        EX_DROP     = 0x30 // 0011 0000 : 드랍 유무 (0 : NONE / 1 : DNA / 2 : FOOD / 3 : URANIUM)
        EX_REGEN    = 0x40 // 0100 0000 : 리젠 유무
        EX_ISBUILD  = 0x80 // 1000 0000 : BUILDING or RESOURCE
    };

    struct EX_DATA {
        enum EX_TYPE TYPE;
        unit16_t health;
        unit16_t health;
    }
    /*
    // 타일 데이터 조작 (인라인 함수로 오버헤드 제거)
    inline bool IsTileOccupied(uint8_t data) { return data & TILE_OCCUPIED; }
    inline bool IsHighGround(uint8_t data)   { return data & TILE_HEIGHT; }
    inline uint8_t GetType(uint8_t data)     { return data & TILE_TYPE; }

    // 데이터 수정 (Set)
    inline void SetOccupied(uint8_t& data, bool occupied) {
        if (occupied) data |= TILE_OCCUPIED;
        else data &= ~TILE_OCCUPIED;
    }
    */


    struct tile{
        double height;
        double temperature;
        double humidity;
        std::array<int,4> color;
        std::string tileType;
        SDL_Rect dst;
    };

    extern tile world[width][height];
}
