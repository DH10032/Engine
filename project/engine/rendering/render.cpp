#include "render.h"

extern "C" {
    
}

namespace GameGrphicApi{
    /**
    * @brief window와 
    * @return 확장자가 정상적일 경우, Texture, 확장자가 지원하지 않을 경우, NULL 입니다.
    */
    typedef struct {
        char* window_name;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int Red;
        int Green;
        int Blue;
        int Bright;
    } window_info;

    /**
    * @brief SLD_system_video 초기화 및, window를 생성
    * @param[in] char* 생생될 window 이름
    * @param[in] Red Red의 배경화면 내용
    * @param[in] Green Green의 배경화면 내용
    * @param[in] Blue Blue의 배경화면 내용
    * @param[in] Bright Bright의 배경화면 내용
    * @param[out] SDL_Renderer* window에 생성될 객체
    * @return 확장자가 정상적일 경우, Texture, 확장자가 지원하지 않을 경우, NULL
    */
    void Create_window(GameGrphicApi::window_info* info){
        std::cout << "run : " << info->window_name << std::endl;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow(
            info->window_name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN
        );
        info->window = window;
        info->renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(info->renderer, info->Red, info->Blue, info->Green, info->Bright);
    }

    SDL_Renderer* Render_window(int Red, int Green, int Blue, int Bright){

    }

    /**
    * @brief jpg,png,bmp를 SDL_Texture*로 변환해주는 함수
    * @param[in] SDL_Renderer* window에 렌러딩할 객체들
    * @param[in] char* path Texture로 바꿀 path
    * @param[out] SDL_Texture* 경로를 변환한 Texture
    * @return 확장자가 정상적일 경우, Texture, 확장자가 지원하지 않을 경우, NULL
    */
    SDL_Texture* Path_to_Texture(SDL_Renderer* renderer, char* path){

        std::filesystem::path p(path);
        std::string png = ".png";
        std::string jpg = ".jpg";
        std::string bmp = ".bmp";
        std::string extension = p.extension().string();

        SDL_Surface* BMP=NULL;
        SDL_Texture* Texture=NULL;

        // 확장자에 따른 SDL_Surface 변환
        if (extension == png) BMP = IMG_Load(path);
        else if (extension == jpg) BMP = IMG_Load(path);
        else if (extension == bmp) BMP = SDL_LoadBMP(path);

        if (BMP==NULL) {
            Texture = SDL_CreateTextureFromSurface(renderer, BMP);
            SDL_FreeSurface(BMP);
            return Texture;
        }
        else
            return NULL;
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

    void Destroy_imgs(SDL_Texture** IMG){
        for (SDL_Texture** i = IMG; *i != NULL; i++){
            
        }
    }

    void Destroy_window(window_info* window_setting){
        SDL_DestroyRenderer(window_setting->renderer);
        SDL_DestroyWindow(window_setting->window);
    }
}

// test2.c - 색상 변경

int main() {
    GameGrphicApi::window_info window_setting {
        .window_name = "test_game",
        .window = NULL,
        .renderer = NULL,
        .Red = 255,
        .Green = 255,
        .Blue = 255,
        .Bright = 255
    };
    GameGrphicApi::Create_window(&window_setting);
    SDL_Surface* BMP = IMG_Load("../../character/bug1.png");
    SDL_Texture* IMG = SDL_CreateTextureFromSurface(window_setting.renderer, BMP);
    SDL_FreeSurface(BMP);

    SDL_Rect dst = {10, 10, 32, 32};
    
    for(;;) {
        SDL_RenderClear(window_setting.renderer);
        SDL_RenderCopy(window_setting.renderer, IMG, NULL, &dst);
        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(500);  // 2초씩
    }
    
    SDL_DestroyRenderer(window_setting.renderer);
    SDL_DestroyWindow(window_setting.window);
    SDL_DestroyTexture(IMG);
    SDL_Quit();
    
    return 0;
}