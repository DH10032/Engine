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
    SDL_SetRenderDrawColor(
        window_setting.renderer,
        window_setting.Red,
        window_setting.Green,
        window_setting.Blue,
        window_setting.Bright
    );
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return -1;
    }

    // SDL_image 초기화
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG Init Error: %s\n", IMG_GetError());
        return -1;
    }

    // SDL_ttf 초기화
    if (TTF_Init() == -1) {
        printf("TTF Init Error: %s\n", TTF_GetError());
        return -1;
    }
    CreateText::TTF_start(window_setting.renderer);


    // 3. World 생성
    worldspace::worldInit();
    SDL_SetRenderDrawBlendMode(window_setting.renderer, SDL_BLENDMODE_BLEND);


    while(true) {
        SDL_SetRenderDrawColor(window_setting.renderer, 255,255,255,255);
        SDL_RenderClear(window_setting.renderer);

        
        for (int x = 0; x < worldspace::width; x++){ // 지형 높이 표현
            for (int y = 0; y < worldspace::height; y++){
                auto color = worldspace::world[x][y].color;
                //std::cout  << "[" << color[0] << "," << color[1] << "," << color[2] << "," << color[3] << "]" << std::endl;
                SDL_SetRenderDrawColor(window_setting.renderer, color[0], color[1], color[2], color[3]);
                SDL_RenderFillRect(window_setting.renderer, &worldspace::world[x][y].dst);

                SDL_Rect test = {100,100,100,100};
                SDL_SetRenderDrawColor(window_setting.renderer, 255,0,0,255);
                SDL_RenderFillRect(window_setting.renderer, &test);
            }
        }

        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(30);
    }
}


void Destroy_window(window_info* window_setting){
    SDL_DestroyRenderer(window_setting->renderer);
    SDL_DestroyWindow(window_setting->window);
    CreateText::TTF_end();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}