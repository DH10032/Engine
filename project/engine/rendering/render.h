#ifndef RENDER
#define RENDER

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>

using json = nlohmann::json;

// 화면 등 기본값
#define  SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/**
 * @brief 윈도우 설정을 위해 필요한 데이터
 */
typedef struct {
    const std::string window_name;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int Red;
    int Green;
    int Blue;
    int Bright;
} window_info;

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

/**
 * @brief 타일의 정보를 저장한 구조체
 * 
 * @par type (int)
 * 타일의 종류 (0, 1, ..)
 * 
 * @par dst (SDL_Rect)
 * 화면에 렌더링될 위치와 크기 (x, y, w, h)
 * 
 * @note 수정될 수도 있음
 */
typedef struct{
    int type;
    SDL_Rect dst;
}title;

namespace GameGraphicApi{
    /**
     * @date 26/2/15
     * @author 이동훈
     * @brief SDL 비디오 시스템 초기화 및 윈도우 생성
     * 
     * @param[in] title 생성될 윈도우의 제목
     * @param[in] flags 생성될 SDL_Window의 설정 플래그
     * @note - 기본 flag: SDL_WINDOW_SHOWN
     * @note - OpenGL flag: SDL_WINDOW_OPENGL
     * @note - 자세한 플래그는 SDL_WindowFlags 참고  
     * 
     * @param[out] renderer 윈도우에 연결될 SDL_Renderer 객체 포인터
     * 
     * @exception renderer혹은 window가 생성되지 않을 경우 에러문구 및 함수 종료
    */
    void Create_window(window_info* info, SDL_WindowFlags flags);
    
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
    Asset Load_Asset(SDL_Renderer* renderer, json json_file);

    /**
    * @brief 윈도우 내 모든 렌더링 제거및 위도우창 닫기(SDL종료)
    */
    void Destroy_window(window_info* window_setting);
}

namespace CreateText { // 미리 선언해두기
    void TTF_start(SDL_Renderer* renderer);
    void TTF_Create(const char* txtContent, int x, int y, int w, int h);
    void TTF_end();
}

#endif