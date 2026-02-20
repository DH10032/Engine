#include "render.h"
 
/* 컴파일

cd project/engine/rendering
g++ render.cpp -o render -lSDL2 -lSDL2_image -lSDL2_ttf
./render -> 실행

-> make로 바뀜

*/




namespace GameGraphicApi{

    void Set_draw_all(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        worldspace::worldInit();
    }
}

namespace CreateAssets{
    typedef struct{ 
        SDL_Texture* texture;
        SDL_Rect dst; // (x,y,tile_width,tile_height)
    }img;
}