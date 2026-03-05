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
/*
    Engine::GameManager system;
    system.ShowWindow();
    system.LoadAsset("Game/data/asset.json");
    
    system.Reg.CreateComponent<worldspace::tile>(Dense);

    for(;;){
        system.DrawObject();
        SDL_Delay(30);
    }

    system.Destroy_Object();
}*/

    window_info window_setting = {
        .window_name = "test_game",
        .window = nullptr,
        .renderer = nullptr,
        .Red = 255,
        .Green = 255,
        .Blue = 255,
        .Bright = 255
    };

    window::Create_window(&window_setting, SDL_WINDOW_SHOWN);
    CreateText::TTF_start(window_setting.renderer);
    SDL_SetRenderDrawColor(
        window_setting.renderer,
        window_setting.Red,
        window_setting.Green,
        window_setting.Blue,
        window_setting.Bright
    );

    // 3. World 생성
    worldspace::worldInit();
    SDL_SetRenderDrawBlendMode(window_setting.renderer, SDL_BLENDMODE_BLEND);


    while(true) {
        SDL_SetRenderDrawColor(window_setting.renderer, 255,255,255,255);
        SDL_RenderClear(window_setting.renderer);

        
        for (int x = 0; x < worldspace::width; x++){ // 지형 높이 표현
            for (int y = 0; y < worldspace::height; y++){
                auto color = worldspace::world[x][y].color;
                SDL_SetRenderDrawColor(window_setting.renderer, color[0], color[1], color[2], color[3]);
                SDL_RenderFillRect(window_setting.renderer, &worldspace::world[x][y].dst);
            }
        }

        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(30);
    }
}

struct tile{
    double height;
    double temperature;
    double humidity;
    std::array<int,4> color;
    std::string tileType;
    SDL_Rect dst;
};

