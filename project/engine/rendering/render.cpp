// test2.c - 색상 변경
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
SDL_CreateRenderer
SDL_SetRenderDrawColor
SDL_RenderClear
*/

namespace GameGrphicApi{
    SDL_Window* Create_window(char* window_name){
        std::cout << "run : " << window_name << std::endl;
        SDL_Init(SDL_INIT_VIDEO);
        // SDL_InitSubSystem(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow(
            window_name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN
        );
        return window;
    }

    void Append(SDL_Texture** ObjLst, SDL_Texture* Obj){
        // 이미지를 메모리에 1열로 배열하는 방식
    }

    void Set_draw_all(SDL_Renderer* renderer, int* Color, int** Obj){
        SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], 255);
        SDL_RenderClear(renderer);
        // 모든 객체 이미지 그리는 for문
    }

    void load_img(int** Obj){
        char* path = "../../character/test.jpg";
    }
}

int main() {
    int White[3] = {255, 255, 255};
    SDL_Window* window = GameGrphicApi::Create_window("test_game");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    // SDL_Surface* BMP = SDL_LoadBMP("../../character/test.bmp");
    SDL_Surface* BMP = IMG_Load("../../character/bug1.png");
    SDL_Texture* IMG = SDL_CreateTextureFromSurface(renderer, BMP);
    SDL_FreeSurface(BMP);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect dst = {10, 10, 32, 32};
    
    for(;;) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, IMG, NULL, &dst);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);  // 2초씩
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(IMG);
    SDL_Quit();
    
    return 0;
}