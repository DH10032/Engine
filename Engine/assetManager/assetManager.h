#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>

using json = nlohmann::json;

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
    std::vector<SDL_Texture*> buildings;
    std::vector<SDL_Texture*> character;
    std::vector<SDL_Texture*> interactives;
    std::vector<SDL_Texture*> tiles;
} Asset;

namespace AssetManager{

    /**
    * @brief jpg,png,bmp를 SDL_Texture*로 변환해주는 함수
    * @param[in] renderer window에 렌러딩할 객체들
    * @param[in] path Texture로 바꿀 path
    * @param[out] SDL_Texture* 경로를 변환한 Texture
    * @return 확장자가 정상적일 경우, Texture, 확장자가 지원하지 않을 경우, nullptr
    */
    SDL_Texture* Path_to_Texture(SDL_Renderer* renderer, const std::string path);
    
    /**
    * @brief Asset 폴더 내부 png파일들을 변환 후, 분리해서 반환
    * @param[in] renderer 이미지를 렌더리할 렌더
    * @param[in] json_file 읽을 json 파일
    * @return Asset(SDL_Texture vector)
    * @note asset.json에 등록해야 함
    * 
    */
    Asset Load_Asset(SDL_Renderer* renderer, std::string path);
}


#endif