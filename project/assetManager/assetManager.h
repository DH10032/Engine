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