#ifndef INTERFACE
#define INTERFACE

#include "../graphic/window/window.h"
#include "../graphic/font/font.h"
#include "../core/assetManager/assetManager.h"

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
            AssetManager::Load_Asset(window_setting.renderer, path);
        }

        void DrawObject(){
            SDL_RenderClear(window_setting.renderer);
            //Animation::Render_Entity(window_setting.renderer, data.character[8], p);
            SDL_RenderPresent(window_setting.renderer);
        }

        private:
        
    };
}

#endif