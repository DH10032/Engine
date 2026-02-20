#ifndef RENDER
#define RENDER

#include "../../../Game/world/world.h"
#include "../../../main.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>

/**
 * @brief 윈도우 설정을 위해 필요한 데이터
 */

namespace GameGraphicApi{
    void Set_draw_all(SDL_Renderer* renderer);
}

namespace CreateText { // 미리 선언해두기
    void TTF_start(SDL_Renderer* renderer);
    void TTF_Create(const char* txtContent, int x, int y, int w, int h);
    void TTF_end();
}

#endif