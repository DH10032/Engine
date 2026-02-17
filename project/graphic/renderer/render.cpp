#include "render.h"
 
/* 컴파일

cd project/engine/rendering
g++ render.cpp -o render -lSDL2 -lSDL2_image -lSDL2_ttf
./render -> 실행

-> make로 바뀜

*/




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
    void Create_window(window_info* info, SDL_WindowFlags flags){
        std::cout << "run : " << info->window_name << std::endl;

        SDL_Window* window = SDL_CreateWindow(
            info->window_name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
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

    SDL_Texture* Path_to_Texture(SDL_Renderer* renderer, const std::string path){

        std::filesystem::path p(path);
        std::string extension = p.extension().string();

        SDL_Texture* Texture = nullptr;
        SDL_Surface* surface = nullptr;

        // 확장자에 따른 SDL_Surface 변환
        if (extension == ".png" || extension == ".jpg")
            surface = IMG_Load(path.c_str());

        else if (extension == ".bmp")
            surface = SDL_LoadBMP(path.c_str());

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

    Asset Load_Asset(SDL_Renderer* renderer, json json_file){
        std::string file_name;
        std::string folder_name;
        std::string path;
        Asset asset;
        for (const auto& [folder, files] : json_file.items()){
            int Imgs_count = files.size();
            std::vector<SDL_Texture*> IMGs;
            for (auto& [idx, f] : files.items()){
                file_name = f;
                folder_name = folder;
                path = "project/assets/"+folder_name+"/"+file_name;
                IMGs.push_back(Path_to_Texture(renderer, path)); 
            }
            if (folder == "buildings") asset.buildings = IMGs;
            else if (folder == "character") asset.character = IMGs;
            else if (folder == "interactives") asset.interactives = IMGs;
            else if (folder == "tiles") asset.tiles = IMGs;
        }
        return asset;
    }

    void Set_draw_all(SDL_Renderer* renderer, int* Color, int** Obj){
        SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], 255);
        SDL_RenderClear(renderer);
        // 모든 객체 이미지 그리는 for문
    }

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