#ifndef ANIMATION
#define ANIMATION

#include "../../hal/HAL.h"

/*
1. 이미지에 떨어져있는 몸체 조립
SDL_Rect

*/

namespace Animation{
    /**
     * @brief Parts를 통해 이미지 조립
     */
    void Render_Entity(SDL_Renderer* renderer, Asset picture ,std::vector<Parts> p);
}

#endif
