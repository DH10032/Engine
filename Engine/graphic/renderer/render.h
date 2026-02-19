#ifndef RENDER
#define RENDER

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

}

namespace CreateText { // 미리 선언해두기
    void TTF_start(SDL_Renderer* renderer);
    void TTF_Create(const char* txtContent, int x, int y, int w, int h);
    void TTF_end();
}

#endif