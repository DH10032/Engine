#ifndef INTERFACE
#define INTERFACE

#include "../graphic/window/window.h"
#include "../graphic/font/font.h"
#include "../core/assetManager/assetManager.h"
#include "../graphic/animation/animation.h"

namespace Engine{
    class Canvas{
        public:
        window_info window_setting = {
            .window_name = "test_game",
            .window = nullptr,
            .renderer = nullptr,
            .Red = 255,
            .Green = 255,
            .Blue = 255,
            .Bright = 255
        };

        Asset data;
        int size = 64;
        std::vector<Parts> p = {
            {
                9,
                {0, 0, 16, 16},
                {200, 200, size, size},
                {size/2, 0},
                0
            },
            {
                9,
                {0, 16, 16, 32},
                {200, 264, size, size},
                {size/2, 0},
                0
            },
            {
                9,
                {48, 48, 64, 64},
                {200, 328, size, size},
                {size/2, 0},
                0
            }
        };

        void ShowWindow(){
            window::Create_window(&window_setting, SDL_WINDOW_SHOWN);
            CreateText::TTF_start(window_setting.renderer);
            SDL_SetRenderDrawColor(
                window_setting.renderer,
                window_setting.Red,
                window_setting.Green,
                window_setting.Blue,
                window_setting.Bright
            );
        }

        void DeleteWindow(){
            window::Destroy_window(&window_setting);
        }

        void LoadAsset(std::string path){
            data = AssetManager::Load_Asset(window_setting.renderer, path);
        }

        void DrawObject(){
            SDL_RenderClear(window_setting.renderer);
            Animation::Render_Entity(window_setting.renderer, data, p);
            SDL_RenderPresent(window_setting.renderer);
        }

        void Destroy_Object(){
            SDL_DestroyRenderer(window_setting.renderer);
            SDL_DestroyWindow(window_setting.window);
            CreateText::TTF_end();
            IMG_Quit();
            SDL_Quit();
        }

        private:
        
    };
}

#endif