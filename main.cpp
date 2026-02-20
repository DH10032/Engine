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
    window_info window_setting {
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

    // 2. AssetManager 초기화
    SDL_Rect destRect = {128, 128, 300, 300};
    Asset data = AssetManager::Load_Asset(window_setting.renderer, "Game/data/asset.json");
    
    int size = 64;

    std::vector<Parts> p = {
        {
            {0, 0, 16, 16},
            {200, 200, size, size},
            {size/2, 0},
            0
        },
        {
            {0, 16, 16, 32},
            {200, 264, size, size},
            {size/2, 0},
            0
        },
        {
            {48, 48, 64, 64},
            {200, 328, size, size},
            {size/2, 0},
            45
        }
        // {
        //     {8, 56, 16, 16},
        //     {200, 248, 16, 16},
        //     {8, 48},
        //     0
        // },
        // {
        //     {56, 56, 16, 16},
        //     {200, 2064, 16, 16},
        //     {56, 48},
        //     0
        // }
    };

    int j = 1;
    for(;;){
        if (p[1].angle > 30)
            j = -1;
        else if (p[1].angle < -30)
            j = 1;
        p[1].angle = p[1].angle + j;
        SDL_RenderClear(window_setting.renderer);
        Animation::Assemble_Texture(window_setting.renderer, data.character[8], p);
        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(30);
    }
}


void Destroy_window(window_info* window_setting){
    SDL_DestroyRenderer(window_setting->renderer);
    SDL_DestroyWindow(window_setting->window);
    CreateText::TTF_end();
    IMG_Quit();
    SDL_Quit();
}