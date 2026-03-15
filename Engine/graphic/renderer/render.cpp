#include "render.h"
 

namespace GameGraphicApi{

    void Set_draw_all(SDL_Renderer* renderer){
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);
    }

    void Render_Entity(SDL_Renderer* renderer, Asset data ,std::vector<Parts> p){
        for(Parts part:p){
            SDL::Render(
                renderer,           // 렌더러
                data.IMGS[part.id], // 텍스처
                part       // 뒤집기 옵션
            );
        }
    }

}