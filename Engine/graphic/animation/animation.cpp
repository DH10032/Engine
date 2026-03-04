#include "animation.h"

/*
0xffffffff
*/
namespace Animation{

    void Render_Entity(SDL_Renderer* renderer, Asset data ,std::vector<Parts> p){


        for(Parts part:p){

            SDL_RenderCopyEx(
                renderer,           // 렌더러
                data.IMGS[part.id], // 텍스처
                &(part.src),        // 소스 영역 (NULL = 전체)
                &(part.dst),        // 목적지 영역
                part.angle,         // 각도 (도 단위, 시계방향)
                &(part.center),     // 회전중심(dst기준 상대 좌표)
                SDL_FLIP_NONE       // 뒤집기 옵션
            );
        }
    }
}
