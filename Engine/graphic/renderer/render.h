#ifndef RENDER
#define RENDER

#include "../../core/memory.h"

/**
 * @brief 윈도우 설정을 위해 필요한 데이터
 */

namespace GameGraphicApi{
    void Set_draw_all(Renderer renderer);
    void Render_Entity(Renderer renderer, Asset data ,DenseComponentPool<Parts>& action_buffer);
}

namespace CreateText { // 미리 선언해두기
    void TTF_start(SDL_Renderer* renderer);
    void TTF_Create(const char* txtContent, int x, int y, int w, int h);
    void TTF_end();
}

#endif