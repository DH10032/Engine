#ifndef SYSTEM
#define SYSTEM

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

typedef char _1byte;
typedef unsigned short _2byte;
typedef unsigned int _4byte;
typedef unsigned long _8byte;

using json = nlohmann::json;


struct {
    _4byte status;      // HP 및 공격력 등
    _2byte debuff;      // 디버프 관리
    _2byte buff;        // 디버프 관리

    _4byte trait_1;     // 기원1 특성
    _4byte trait_2;     // 기원2 특성

    _4byte trait_3;     // 기원3 특성
    _4byte trait_4;     // 기원4 특성

    _4byte action;      // 행동 id
    _4byte command;     // 명령 데이터
} Unit;

namespace memory{
    /**
     * @brief json을 읽어주는 함수
     * @param[in] path 읽고 싶은 json 경로 입력하면 됨
     * 
     * @note 임시 함수 원래는 memory.cpp에 있어야 함
     * @note core.cpp 기준으로 입력하면 됨(자동으로 변환 기능이 있음)
     * 
     * @verbatim Load_Action_json("data/asset.json");
    */
    json Load_Action_json(std::string path);

}

#endif