#include "font.h"



SDL_Renderer* TXT_renderer; // init에서 한번 호출 후 쭉 쓸수 있게

TTF_Font* bitlimFont; // 많아지면 배열로 관리?

namespace CreateText{
    void TTF_start(SDL_Renderer* renderer){
        TXT_renderer = renderer;
        if (TTF_Init() == -1){
            std::cout << "Failed to load font." << std::endl;
        } else {
            bitlimFont = TTF_OpenFont("project/assets/fonts/bitlim.ttf", 30); // 30 뭔지 모르겠음
            if(bitlimFont == NULL) {
                printf("Could not open font! (%s)\n", TTF_GetError());
            }
        }
    
    }
    
    void TTF_end(){
        TTF_CloseFont(bitlimFont); // 많아지면 for 돌릴 예정
    }
    
    void TTF_Create(const char* txtContent, int x, int y, int w, int h){ // 글 내용, x,y,width,height (앞으로 간단히 그릴 수 있도록 함수 제작)
        SDL_Rect Rct = { x, y, w, h };
        SDL_Surface* FSurface = TTF_RenderText_Blended(bitlimFont, txtContent, (SDL_Color){ 0, 0, 0 }); // 일단 색상은 검정 통일, 이후 수정 예정
        SDL_Texture* FTexture = SDL_CreateTextureFromSurface(TXT_renderer, FSurface);
        SDL_RenderCopy(TXT_renderer, FTexture, NULL, &Rct);
    }
}