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

        for (int x = 0; x < 99; x++) {
            for (int y = 0; y < 99; y++) {

                
                float bright = worldspace::GetTile(x,y).bright * 255;
                SDL_SetRenderDrawColor(renderer, 30, 255, 30, bright);
                SDL_RenderFillRect(renderer, &worldspace::GetTile(x,y).dst);
            }
        }

        SDL_RenderPresent(renderer);
    }
}

namespace CreateAssets{
    typedef struct{ 
        SDL_Texture* texture;
        SDL_Rect dst; // (x,y,tile_width,tile_height)
    }img;
}