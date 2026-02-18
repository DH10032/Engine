#include "Object.h"


// 일단 여기로 뺴놨는데 나중에 units.cpp 같은거 하나 만들어야될듯 2222
namespace Object{
    json Load_Action_json(const std::string path){
        std::ifstream file(path);
        json data = json::parse(file);
        return data;
    }
}