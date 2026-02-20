#include "animation.h"


namespace Animation{

    void Assemble_Texture(SDL_Renderer* renderer, SDL_Texture* picture ,std::vector<Parts> p){
        int x = 0;
        int y = 0;
        int r = 16;
        for(Parts part:p){
            // part.dst.x = x;
            // part.dst.y = y;
            // r sin theta
            // r cosin theta
            SDL_RenderCopyEx(
                renderer,           // 렌더러
                picture,            // 텍스처
                &(part.src),        // 소스 영역 (NULL = 전체)
                &(part.dst),        // 목적지 영역
                part.angle,         // 각도 (도 단위, 시계방향)
                &(part.center),     // 회전중심(dst기준 상대 좌표)
                SDL_FLIP_NONE       // 뒤집기 옵션
            );
        }
    }

    void update_Texture(std::vector<Parts> p){

    }
}
