#ifndef ANIMATION
#define ANIMATION

#include <SDL2/SDL.h>
/*
1. 이미지에 떨어져있는 몸체 조립
SDL_Rect

*/

typedef struct{
    SDL_Rect src;
    SDL_Point center;
    int angle;
}Parts;



#endif