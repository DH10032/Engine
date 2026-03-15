#ifndef _HAL_
#define _HAL_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <glm/glm.hpp>
#include <algorithm>

#include <cmath>
#include <array>
#include <numeric>
#include <map>
#include <typeindex>
#include <vector>
#include<cassert>

using json = nlohmann::json;

typedef SDL_Texture* Texture;

typedef SDL_Renderer* Renderer;

/**
 * @brief Asset을 변환해 폴더별로 분류해 저장가능한 자료
 * 
 * @par buildings (std::vector<SDL_Texture*>)
 * 
 * @par character (std::vector<SDL_Texture*>)
 * 
 * @par interactives (std::vector<SDL_Texture*>)
 * 
 * @par tiles (std::vector<SDL_Texture*>)
 * 
 * @note 수정될 수도 있음
 */
typedef struct {
    std::vector<SDL_Texture*> IMGS;
} Asset;

typedef struct {
   const char* window_name;
   SDL_Window* window;
   SDL_Renderer* renderer;
   int Red;
   int Green;
   int Blue;
   int Bright;
} window_info;

/**
 * 
 */
typedef struct{
    unsigned int id;
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Point center;
    int angle;
    bool IsFlip;
}Parts;

/*
SDL_RenderCopyEx(
    renderer,           // 렌더러
    data.IMGS[part.id], // 텍스처
    &(part.src),        // 소스 영역 (NULL = 전체)
    &(part.dst),        // 목적지 영역
    part.angle,         // 각도 (도 단위, 시계방향)
    &(part.center),     // 회전중심(dst기준 상대 좌표)
    SDL_FLIP_NONE       // 뒤집기 옵션
);
*/
namespace HAL{
    void Render(Renderer renderer, Texture Picture ,Parts part);
}

#endif
