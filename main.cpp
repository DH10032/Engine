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
    int MAPSIZE = 2048;
    mapspace::Map myMap(MAPSIZE,MAPSIZE);
    system.ShowWindow();
    system.LoadAsset("Game/data/asset.json");
    
    //system.Reg.CreateComponent<worldspace::tile>(Dense);


    std::vector<std::vector<int>> tile_color_datas = {
        {0, 100, 200, 255},
        {120, 180, 80, 255},
        {34, 139, 34, 255},
        {0, 80, 0, 255},
        {240, 200, 100, 255},
        {200, 180, 50, 255},
        {30, 80, 60, 255},
        {100, 200, 50, 255},
        {150, 160, 150, 255},
        {130, 120, 110, 255},
        {47, 79, 79, 255},
        {200, 220, 240, 255},
        {160, 190, 220, 255},
        {245, 250, 255, 255},
        {180, 230, 255, 255},
        {150, 50, 50, 255}
    };

    while(true){
        system.FrameStart();

        for (int y = 0; y <MAPSIZE; y++)
            for (int x = 0; x <MAPSIZE; x++)
               system.DrawMap(x,y,1,1,tile_color_datas[myMap.GetTileType(x,y)]);
        // for (int cy=0; cy<Map.chunkHeight; ++cy){
        //     for (int cx=0; cx<Map.chunkWidth; ++cx){
        //         for (int ly=0; ly<SIZE; ++ly){
        //             for (int lx=0; lx<SIZE; ++lx)
        //             {
        //                 Engine::GameManager::DrawMap()
        //             }
        //         }
        //     }
        // }
        system.FrameEnd();
        SDL_Delay(30);
    }
}