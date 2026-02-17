#include "engine/rendering/render.h"
#include "engine/system/system.h"

int main() {
    window_info window_setting {
        .window_name = "test_game",
        .window = nullptr,
        .renderer = nullptr,
        .Red = 255,
        .Green = 255,
        .Blue = 255,
        .Bright = 255
    };

    
    
    GameGraphicApi::Create_window(&window_setting, SDL_WINDOW_SHOWN);

    title ground { // -> 이것도 위와 같이 JSON서 이미지들 한번에 불러오는 함수 만들면 될듯
        .type = 0,
        .dst = {0,0,32,32}
    };

    Asset data = GameGraphicApi::Load_Asset(window_setting.renderer, memory::Load_Action_json("project/data/asset.json"));
    
    // ========================================== 기본설정 ==========================================


    SDL_Rect dst = {10, 10, 32, 32};

    bool running = true;
    while(running) {
        SDL_RenderClear(window_setting.renderer);


        for (int y = 0; y < SCREEN_HEIGHT; y += 32) {
            for (int x = 0; x < SCREEN_WIDTH; x += 32) {

                ground.dst.x = x;
                ground.dst.y = y;
                if (!ground.type) std::cout << "ground texture load failed\n";
                else SDL_RenderCopy(window_setting.renderer, data.tiles[ground.type], NULL, &ground.dst);
            }
        }
        CreateText::TTF_Create("hihi",100,100,100,100); // 테스트 출력

        SDL_RenderPresent(window_setting.renderer);
        SDL_Delay(8); // 약 120FPS
    }
    
    GameGraphicApi::Destroy_window(&window_setting);
    
    return 0;
}