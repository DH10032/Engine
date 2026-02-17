#ifndef SYSTEM
#define SYSTEM

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

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