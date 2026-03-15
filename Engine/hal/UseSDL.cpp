#include "HAL.h"

namespace SDL{
    void Render(Renderer renderer, Texture* Picture ,Parts part){
        SDL_RenderCopyEx(
            renderer,           // 렌더러
            Picture,            // 텍스처
            &(part.src),        // 소스 영역 (NULL = 전체)
            &(part.dst),        // 목적지 영역
            part.angle,         // 각도 (도 단위, 시계방향)
            &(part.center),     // 회전중심(dst기준 상대 좌표)
            part.IsFlip       // 뒤집기 옵션
        );
    }
}