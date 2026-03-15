#ifndef RENDER
#define RENDER

#include <vector>
#include "../../hal/HAL.h"

/**
 * @brief 윈도우 설정을 위해 필요한 데이터
 */

namespace GameGraphicApi{
    void Set_draw(SDL_Renderer* renderer, int x, int y, int w, int h, std::vector<int> color);
}

namespace CreateText { // 미리 선언해두기
    void TTF_start(SDL_Renderer* renderer);
    void TTF_Create(const char* txtContent, int x, int y, int w, int h);
    void TTF_end();
}

#endif