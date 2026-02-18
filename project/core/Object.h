#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


typedef signed char _1byte;
typedef unsigned short _2byte;
typedef unsigned int _4byte;
typedef unsigned long _8byte;


using json = nlohmann::json;

/*
SDL_RenderCopyEx(
    renderer,       // 렌더러
    texture,        // 텍스처
    NULL,           // 소스 영역 (NULL = 전체)
    &destRect,      // 목적지 영역
    45.0,           // 각도 (도 단위, 시계방향)
    NULL,           // 회전 중심점 (NULL = 중앙)
    SDL_FLIP_NONE   // 뒤집기 옵션
);
메모장
*/

/*
// status 4바이트 구조
[체력 8bit][공격력 8bit]

// IMG
[이미지 ID 18bit][특수효과 8bit][진영 4bit][Flip 2bit]

// command 4바이트 구조
[명령타입 8bit][우선순위 8bit][목표타입 8bit][진행상태 8bit]

// 예시
- 명령타입: ATTACK=1, DEFEND=2, GATHER=3, SCOUT=4...
- 우선순위: 0~255 (높을수록 우선)
- 목표타입: ENEMY=1, RESOURCE=2, LOCATION=3...
- 진행상태: IDLE=0, MOVING=1, EXECUTING=2, COMPLETE=3
*/

struct {
    _2byte HP;          // HP
    _2byte attack;      // 공격력
    _2byte debuff;      // 디버프 관리
    _2byte buff;        // 디버프 관리

    _2byte x;           // unit 위치
    _2byte y;           // unit type
    _2byte size_x;      // 이미지 x
    _2byte size_y;      // 이미지 y

    _1byte v_x;         // x방향 속도
    _1byte v_y;         // y방향 속도
    _2byte angle;        // 이미지 뒤집기
    _4byte Img;         // 이미지 ID, 이미지 뒤집기

    _4byte trait_1;     // 기원1 특성
    _4byte trait_2;     // 기원2 특성

    _4byte trait_3;     // 기원3 특성
    _4byte trait_4;     // 기원4 특성

    _4byte action;      // 행동 id
    _4byte command;     // 명령 데이터
} Unit;

struct {
    _2byte x;           // unit 위치
    _2byte y;           // unit type
    _2byte size_x;      // 이미지 x
    _2byte size_y;      // 이미지 y

    _1byte reserved;    // 남는 공간 (padding)
    _1byte Flip;        // 이미지 뒤집기
    _2byte angle;       // 이미지 각도
    _4byte Img;         // 이미지 ID
} Tile;

namespace Object{
    /**
     * @brief json을 읽어주는 함수
     * @param[in] path 읽고 싶은 json 경로 입력하면 됨
     * 
     * @note 임시 함수 원래는 memory.cpp에 있어야 함
     * @note core.cpp 기준으로 입력하면 됨(자동으로 변환 기능이 있음)
     * 
     * @verbatim Load_Action_json("data/asset.json");
    */
    json Load_Action_json(const std::string path);

}