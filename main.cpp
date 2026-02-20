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


    int w, h;
    SDL_GetRendererOutputSize(window_setting.renderer, &w, &h);
    printf("Output size: %d x %d\n", w, h);

    SDL_GetWindowSize(window_setting.window, &w, &h);
    printf("Window size: %d x %d\n", w, h);


    // 3. World 생성
    worldspace::worldInit();
    worldspace::waterInit();
    SDL_SetRenderDrawBlendMode(window_setting.renderer, SDL_BLENDMODE_BLEND);


    while(true) {
        GameGraphicApi::Set_draw_all(window_setting.renderer);
        
        for (int x = 0; x < worldspace::width; x++){ // 지형 높이 표현
            for (int y = 0; y < worldspace::height; y++){
                int bright = worldspace::world[x][y].bright;
                SDL_SetRenderDrawColor(window_setting.renderer, 0, 255, 0, bright);
                SDL_RenderFillRect(window_setting.renderer, &worldspace::world[x][y].dst);
            }
        }
        for (int x = 0; x < worldspace::width; x++){ // 물 표현
            for (int y = 0; y < worldspace::height; y++){
                int watered = worldspace::water[x][y].bright;
                SDL_SetRenderDrawColor(window_setting.renderer, 0, 0, 255 - watered, watered);
                SDL_RenderFillRect(window_setting.renderer, &worldspace::water[x][y].dst);
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
    IMG_Quit();
    SDL_Quit();
}