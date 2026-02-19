#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>


namespace CreateText { // 미리 선언해두기


    /**
    * @brief TTF init 및 기본 설정
    * @param[in] renderer 이미지를 렌더리할 렌더
    * @note main.h 에서 사용중
    */
    void TTF_start(SDL_Renderer* renderer);

    
    /**
    * @brief TTF 생성 함수
    * @param[in] txtContent text내용
    * @param[in] x, y, w, h 생성할 text의 X 좌표, Y 좌표, width, height
    */
    void TTF_Create(const char* txtContent, int x, int y, int w, int h);


    /**
    * @brief TTF 종료 함수
    */
    void TTF_end();
}