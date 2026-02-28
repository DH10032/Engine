#include "main.h"

int main()
{
    // 1. Window / Renderer 생성 및 SDL 초기화
    // 2. AssetManager 초기화
    // 3. World 생성
    // 4. Core(GameState) 생성
    // 5. Renderer / Camera 생성
    // 6. 게임 루프
    //      - 이벤트 처리
    //      - 입력 처리
    //      - 코어 업데이트
    //      - AI 업데이트
    //      - 렌더링
    //      - 프레임 제한
    // 7. 리소스 정리


    // 1. Window / Renderer 생성 및 SDL 초기화
    Engine::Canvas Window;
    Window.ShowWindow();
    Window.LoadAsset("Game/data/asset.json");

    for(;;){
        Window.DrawObject();
        SDL_Delay(30);
    }

    Window.Destroy_Object();
}