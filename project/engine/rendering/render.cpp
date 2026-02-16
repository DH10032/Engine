#include "render.h"

 
// 컴파일
// cd project/engine/rendering
// g++ render.cpp -o render -lSDL2 -lSDL2_image -lSDL2_ttf
// ./render -> 실행


// 화면 등 기본값
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// 색깔
SDL_Color BLACK = { 0, 0, 0 };


namespace CreateText { // 미리 선언해두기
    void TTF_start(SDL_Renderer* renderer);
    void TTF_end();
}




namespace GameGraphicApi{

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
    void Create_window(window_info* info, SDL_WindowFlags flags){
        std::cout << "run : " << info->window_name << std::endl;

        SDL_Window* window = SDL_CreateWindow(
            info->window_name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            flags
        );

        info->window = window;
        if (!info->window) {
            std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
            return;
        }

        info->renderer = SDL_CreateRenderer(window, -1, 0);
        if (!info->renderer) {
            std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
            return;
        }

        SDL_SetRenderDrawColor(
            info->renderer,
            info->Red,
            info->Green,
            info->Blue,
            info->Bright
        );

        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        CreateText::TTF_start(info->renderer); // init 과 동시에 renderer 정의
    }

    /**
    * @brief jpg,png,bmp를 SDL_Texture*로 변환해주는 함수
    * @param[in] renderer window에 렌러딩할 객체들
    * @param[in] path Texture로 바꿀 path
    * @param[out] SDL_Texture* 경로를 변환한 Texture
    * @return 확장자가 정상적일 경우, Texture, 확장자가 지원하지 않을 경우, nullptr
    */
    SDL_Texture* Path_to_Texture(SDL_Renderer* renderer, const char* path){

        std::filesystem::path p(path);
        std::string extension = p.extension().string();

        SDL_Texture* Texture = nullptr;
        SDL_Surface* surface = nullptr;

        // 확장자에 따른 SDL_Surface 변환
        if (extension == ".png" || extension == ".jpg")
            surface = IMG_Load(path);

        else if (extension == ".bmp")
            surface = SDL_LoadBMP(path);

        if (!surface) {
            if (extension == ".bmp")
                std::cout << "BMP Load Error: " << SDL_GetError() << std::endl;
            else
                std::cout << "Image Load Error: " << IMG_GetError() << std::endl;
            return nullptr;
        }
        
        Texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!Texture)
            return nullptr;

        return Texture;
    }

    /**
    * @brief 현재 미완 사용하지 말 것
    */
    void Set_draw_all(SDL_Renderer* renderer, int* Color, int** Obj){
        SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], 255);
        SDL_RenderClear(renderer);
        // 모든 객체 이미지 그리는 for문
    }

    /**
    * @brief 윈도우 내 모든 렌더링 제거및 위도우창 닫기(SDL종료)
    */
    void Destroy_window(window_info* window_setting){
        SDL_DestroyRenderer(window_setting->renderer);
        SDL_DestroyWindow(window_setting->window);
        CreateText::TTF_end();
        IMG_Quit();
        SDL_Quit();
    }

}

namespace CreateAssets{
    typedef struct{ 
        SDL_Texture* texture;
        SDL_Rect dst; // (x,y,tile_width,tile_height)
    }img;
}

namespace CreateText{
    SDL_Renderer* TXT_renderer; // init에서 한번 호출 후 쭉 쓸수 있게

    TTF_Font* bitlimFont; // 많아지면 배열로 관리?

    void TTF_start(SDL_Renderer* renderer){
        TXT_renderer = renderer;
        if (TTF_Init() == -1){
            std::cout << "Failed to load font." << std::endl;
        } else {
            bitlimFont = TTF_OpenFont("../../assets/fonts/bitlim.ttf", 30); // 30 뭔지 모르겠음
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
        SDL_Surface* FSurface = TTF_RenderText_Blended(bitlimFont, txtContent, BLACK); // 일단 색상을 검정 통일, 이후 수정 예정
        SDL_Texture* FTexture = SDL_CreateTextureFromSurface(TXT_renderer, FSurface);
        SDL_RenderCopy(TXT_renderer, FTexture, NULL, &Rct);
    }
}




int main() {
    GameGraphicApi::window_info window_setting {
        .window_name = "test_game",
        .window = nullptr,
        .renderer = nullptr,
        .Red = 255,
        .Green = 255,
        .Blue = 255,
        .Bright = 255
    };
    GameGraphicApi::Create_window(&window_setting, SDL_WINDOW_SHOWN);

    CreateAssets::img ground { // -> 이것도 위와 같이 JSON서 이미지들 한번에 불러오는 함수 만들면 될듯
        .texture = GameGraphicApi::Path_to_Texture(window_setting.renderer, "../../assets/img/tiles/grass.png"),
        .dst = {0,0,32,32}
    };

    // ========================================== 기본설정 ==========================================


    SDL_Rect dst = {10, 10, 32, 32};
    SDL_Texture* IMG = GameGraphicApi::Path_to_Texture(window_setting.renderer, "../../assets/img/character/bug1.png");
    if (!IMG) {
        std::cout << "Failed to load texture." << std::endl;
        GameGraphicApi::Destroy_window(&window_setting);
        return -1;
    }

    bool running = true;
    while(running) {
        SDL_RenderClear(window_setting.renderer);


        for (int y = 0; y < SCREEN_HEIGHT; y += 32) {
            for (int x = 0; x < SCREEN_WIDTH; x += 32) {

                ground.dst.x = x;
                ground.dst.y = y;
                if (!ground.texture) {
                    std::cout << "ground texture load failed\n";
                }
                else{
                    SDL_RenderCopy(window_setting.renderer, ground.texture, NULL, &ground.dst);
                }
            }
        }
        CreateText::TTF_Create("hihi",100,100,100,100); // 테스트 출력
        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(16); // 약 60FPS
    }
    
    GameGraphicApi::Destroy_window(&window_setting);
    
    return 0;
}