#include "render.h"
 
// 컴파일
// cd project/engine/rendering
// g++ render.cpp -o render -lSDL2 -lSDL2_image
// ./render -> 실행


// 화면 등 기본값
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;



namespace GameGraphicApi{

    typedef struct {
        const std::string window_name;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int Red;
        int Green;
        int Blue;
        int Bright;
    } window_info;

    typedef struct {
        std::vector<SDL_Texture*> buildings;
        std::vector<SDL_Texture*> character;
        std::vector<SDL_Texture*> interactives;
        std::vector<SDL_Texture*> tiles;
    } Asset;

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
    void Create_window(GameGraphicApi::window_info* info, SDL_WindowFlags flags){
        std::cout << "run : " << info->window_name << std::endl;
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        SDL_Window* window = SDL_CreateWindow(
            info->window_name.c_str(),
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

        info->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    }

    /**
    * @brief jpg,png,bmp를 SDL_Texture*로 변환해주는 함수
    * @param[in] renderer window에 렌러딩할 객체들
    * @param[in] path Texture로 바꿀 path
    * @param[out] SDL_Texture* 경로를 변환한 Texture
    * @return 확장자가 정상적일 경우, Texture, 확장자가 지원하지 않을 경우, nullptr
    */
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

    /**
     * @brief json을 읽어주는 함수
     * @param[in] path 읽고 싶은 json 경로 입력하면 됨
     * 
     * @note 임시 함수 원래는 memory.cpp에 있어야 함
     * @note core.cpp 기준으로 입력하면 됨(자동으로 변환 기능이 있음)
     * 
     * @verbatim Load_Action_json("data/asset.json");
     * 
    */
    json Load_Action_json(const std::string path){
        std::ifstream file(("../../"+path).c_str());
        json data = json::parse(file);
        return data;
    }

    /**
     * @brief Asset 폴더 내부 png파일들을 변환 후, 분리해서 반환
     * @param[in] renderer 이미지를 렌더리할 렌더
     * @param[in] json_file 읽을 json 파일
     * @return Asset(SDL_Texture vector)
     * @note asset.json에 등록해야 함
     * 
    */
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
                path = "../../assets/"+folder_name+"/"+file_name;
                IMGs.push_back(Path_to_Texture(renderer, path)); 
            }
            if (folder == "buildings") asset.buildings = IMGs;
            else if (folder == "character") asset.character = IMGs;
            else if (folder == "interactives") asset.interactives = IMGs;
            else if (folder == "tiles") asset.tiles = IMGs;
        }
        return asset;
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
        IMG_Quit();
        SDL_Quit();
    }

}

/* 
    어따 만들지 몰라서 일단 여기에 만들었는데
    나중에 data에 json만들고 거기에 이미지 정보들 다 넣은담에 한번에 빼서 구조체로 만드는 함수 만드는게 좋을듯  
    .                                                                                                           */
typedef struct{ 
    SDL_Texture* texture;
    SDL_Rect dst; // (x,y,tile_width,tile_height)
}img;




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

    img ground { // -> 이것도 위와 같이 JSON서 이미지들 한번에 불러오는 함수 만들면 될듯
        .texture = GameGraphicApi::Path_to_Texture(window_setting.renderer, "../../assets/tiles/grass.png"),
        .dst = {0,0,32,32}
    };

    GameGraphicApi::Asset data = GameGraphicApi::Load_Asset(window_setting.renderer, GameGraphicApi::Load_Action_json("data/asset.json"));
    
    // ========================================== 기본설정 ==========================================


    SDL_Rect dst = {10, 10, 32, 32};
    // SDL_Texture* IMG = GameGraphicApi::Path_to_Texture(window_setting.renderer, "../../assets/character/bug1.png");
    // if (!IMG) {
    //     std::cout << "Failed to load texture." << std::endl;
    //     GameGraphicApi::Destroy_window(&window_setting);
    //     return -1;
    // }

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
                    SDL_RenderCopy(window_setting.renderer, data.buildings[0], NULL, &ground.dst);
                }
            }
        }
        
        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(16); // 약 60FPS
    }
    
    GameGraphicApi::Destroy_window(&window_setting);
    
    return 0;
}