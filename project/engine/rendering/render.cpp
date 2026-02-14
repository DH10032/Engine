#include <iostream>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace GameGraphicApi {

    typedef struct {
        const char* window_name;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int Red;
        int Green;
        int Blue;
        int Bright;
    } window_info;


    bool Create_window(window_info* info) {

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cout << "SDL Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
            std::cout << "SDL_image Init Error: " << IMG_GetError() << std::endl;
            return false;
        }

        info->window = SDL_CreateWindow(
            info->window_name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN
        );

        if (!info->window) {
            std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
            return false;
        }

        info->renderer = SDL_CreateRenderer(info->window, -1, SDL_RENDERER_ACCELERATED);

        if (!info->renderer) {
            std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
            return false;
        }

        // 하얀색 배경화면
        SDL_SetRenderDrawColor(
            info->renderer,
            info->Red,
            info->Green,
            info->Blue,
            info->Bright
        );

        return true;
    }


    SDL_Texture* Path_to_Texture(SDL_Renderer* renderer, const char* path) {

        std::filesystem::path p(path);
        std::string extension = p.extension().string();

        SDL_Surface* surface = nullptr;

        if (extension == ".png" || extension == ".jpg") {
            surface = IMG_Load(path);
        }
        else if (extension == ".bmp") {
            surface = SDL_LoadBMP(path);
        }

        if (!surface) {
            std::cout << "Image Load Error: " << IMG_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture) {
            std::cout << "Texture Creation Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        return texture;
    }


    void Destroy_window(window_info* info) {

        if (info->renderer)
            SDL_DestroyRenderer(info->renderer);

        if (info->window)
            SDL_DestroyWindow(info->window);

        IMG_Quit();
        SDL_Quit();
    }

}



int main() {

    GameGraphicApi::window_info window_setting{
        "test_game",
        nullptr,
        nullptr,
        255, 255, 255, 255
    };

    if (!GameGraphicApi::Create_window(&window_setting))
        return -1;


    SDL_Texture* IMG =
        GameGraphicApi::Path_to_Texture(
            window_setting.renderer,
            "../../character/bug1.png"
        );

    if (!IMG)
        return -1;


    SDL_Rect dst = { 10, 10, 64, 64 };

    bool running = true;
    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(
            window_setting.renderer,
            255, 255, 255, 255
        );

        SDL_RenderClear(window_setting.renderer);

        SDL_RenderCopy(
            window_setting.renderer,
            IMG,
            nullptr,
            &dst
        );

        SDL_RenderPresent(window_setting.renderer);

        SDL_Delay(16); // 약 60FPS
    }

    SDL_DestroyTexture(IMG);
    GameGraphicApi::Destroy_window(&window_setting);

    return 0;
}
