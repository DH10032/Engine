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


    // 1. SDL 초기화
    window_info window_setting {
        .window_name = "test_game",
        .window = nullptr,
        .renderer = nullptr,
        .Red = 255,
        .Green = 255,
        .Blue = 255,
        .Bright = 255
    };

    SDL_Window* window = SDL_CreateWindow(
        "test_game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Rect destRect = {128, 128, 300, 300};

    window_setting.window = window;
    if (!window_setting.window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    window_setting.renderer = SDL_CreateRenderer(window, -1, 0);
    if (!window_setting.renderer) {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_SetRenderDrawColor(
        window_setting.renderer,
        window_setting.Red,
        window_setting.Green,
        window_setting.Blue,
        window_setting.Bright
    );


    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    CreateText::TTF_start(window_setting.renderer);
    Asset data = AssetManager::Load_Asset(window_setting.renderer, "project/data/asset.json");


    


    int i = 5;
    int j = 1;
    // i = 6 7 8 7 6 7 8 ...
    for(;;){

        if (i == 7)
            j = -1;
        else if (i == 5)
            j = 1;
        std::cout<< i <<std::endl;
        SDL_RenderClear(window_setting.renderer);
        // 사슴벌레 몸 렌더링
        SDL_RenderCopyEx(
            window_setting.renderer,       // 렌더러
            data.character[1],        // 텍스처
            NULL,           // 소스 영역 (NULL = 전체)
            &destRect,      // 목적지 영역
            0,           // 각도 (도 단위, 시계방향)
            NULL,           // 회전 중심점 (NULL = 중앙)
            SDL_FLIP_NONE   // 뒤집기 옵션
        );

        // 사슴벌레 집게 렌더링
        SDL_RenderCopyEx(
            window_setting.renderer,       // 렌더러
            data.character[2],        // 텍스처
            NULL,           // 소스 영역 (NULL = 전체)
            &destRect,      // 목적지 영역
            0,           // 각도 (도 단위, 시계방향)
            NULL,           // 회전 중심점 (NULL = 중앙)
            SDL_FLIP_NONE   // 뒤집기 옵션
        );

        // 사슴벌레 몸 렌더링
        SDL_RenderCopyEx(
            window_setting.renderer,       // 렌더러
            data.character[i],        // 텍스처
            NULL,           // 소스 영역 (NULL = 전체)
            &destRect,      // 목적지 영역
            0,           // 각도 (도 단위, 시계방향)
            NULL,           // 회전 중심점 (NULL = 중앙)
            SDL_FLIP_NONE   // 뒤집기 옵션
        );
        
        SDL_RenderPresent(window_setting.renderer);

        i = i + j;
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