#include "render.h"
 
/* 컴파일

cd project/engine/rendering
g++ render.cpp -o render -lSDL2 -lSDL2_image -lSDL2_ttf
./render -> 실행

-> make로 바뀜

*/




namespace GameGraphicApi{

    void Set_draw_all(SDL_Renderer* renderer, int* Color, int** Obj){
        SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], 255);
        SDL_RenderClear(renderer);
        // 모든 객체 이미지 그리는 for문
    }
}

namespace CreateAssets{
    typedef struct{ 
        SDL_Texture* texture;
        SDL_Rect dst; // (x,y,tile_width,tile_height)
    }img;
}