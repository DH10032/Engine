#include "../graphic/renderer/render.h"
#include "../graphic/font/font.h"
#include "../assetManager/assetManager.h"
#include "../world/world.h"
#include "../main.h"

int main() {


    
    // ========================================== 기본설정 ==========================================


    SDL_Rect dst = {10, 10, 32, 32};

    bool running = true;
    while(running) {
        SDL_RenderClear(window_setting->renderer);


        for (auto& worldx : worldspace::world) {
            for (auto& tile : worldx) {

                ground.dst.x = x;
                ground.dst.y = y;
                if (!ground.type) std::cout << "ground texture load failed\n";
                else SDL_RenderCopy(window_setting->renderer, data.tiles[ground.type], NULL, &ground.dst);
            }
        }

        SDL_RenderPresent(window_setting->renderer);
        SDL_Delay(8); // 약 120FPS
    }
    
    return 0;
}