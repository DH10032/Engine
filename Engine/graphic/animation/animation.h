#ifndef ANIMATION
#define ANIMATION

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <cmath>

/*
1. 이미지에 떨어져있는 몸체 조립
SDL_Rect

*/

typedef struct{
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Point center;
    int angle;
}Parts;

namespace Animation{
    /**
     * @brief Parts를 통해 이미지 조립
     */
    void Assemble_Texture(SDL_Renderer* renderer, SDL_Texture* picture ,std::vector<Parts> p);

    void UpdateTraslation(std::vector<Parts>& part, std::vector<int> action, int tmp);
}

#endif
