#include "system.h"

typedef char _1byte;
typedef unsigned short _2byte;
typedef unsigned int _4byte;
typedef unsigned long _8byte;

// padding 고려해서 제거하기

// struct {
//     _4byte status;      // HP 및 공격력 등
//     _2byte debuff;      // 디버프 관리
//     _2byte buff;        // 디버프 관리
//     _4byte action;      // 행동 id
// } Unit;

// json Load_Action_json(){
//     std::ifstream file("../../data/action.json");
//     json data = json::parse(file);
//     return data;
// }

// int main(){
//     json a = Load_Action_json();
//     std::cout << a.dump(2);
// }