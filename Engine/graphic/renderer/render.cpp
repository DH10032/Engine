#include "render.h"
 

namespace GameGraphicApi{

    void Set_draw_all(Renderer renderer){
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);
    }

    void Render_Entity(Renderer renderer, Asset data ,std::vector<Parts> p){
        for(Parts part:p){
            HAL::Render(
                renderer,           // 렌더러
                data.IMGS[part.id], // 텍스처
                part       // 뒤집기 옵션
            );
        }
    }

}