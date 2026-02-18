#ifndef MAIN
#define MAIN

#include "world/world.h"
#include "graphic/font/font.h"
#include "graphic/renderer/render.h"
#include "graphic/renderer/shader.h"
#include "assetManager/assetManager.h"
#include "core/types.h"

// 화면 등 기본값
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600




window_info* window_setting;


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
* @brief 윈도우 내 모든 렌더링 제거및 위도우창 닫기(SDL종료)
*/
void Destroy_window(window_info* window_setting);

#endif