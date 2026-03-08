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

    Engine::GameManager system;
    system.ShowWindow();
    system.LoadAsset("Game/data/asset.json");
    
    system.Reg.CreateComponent<worldspace::tile>(Dense);

    for(;;){
        system.FrameStart();
        mapspace::map(1024,1024);
        for (int cy=0; cy<map.chunkHeight; ++cy){
            for (int cx=0; cx<map.chunkWidth; ++cx){
                for (int ly=0; ly<SIZE; ++ly){
                    for (int lx=0; lx<SIZE; ++lx)
                    {
                        
                    }
                }
        }
        SDL_Delay(30);
    }
}