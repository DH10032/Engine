typedef char _1byte;
typedef unsigned short _2byte;
typedef unsigned int _4byte;
typedef unsigned long _8byte;

// padding 고려해서 제거하기

struct {
    _2byte status;
    _2byte debuff;
    _2byte buff;    
    _4byte action;
} Unit;