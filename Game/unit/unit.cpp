#include "unit.h"


namespace Object{
    json Load_Action_json(const std::string path){
        std::ifstream file(path);
        json data = json::parse(file);
        return data;
    }
    

}

