#include "GameManager.h"



void Engine::GameManager::ShowWindow(){
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

void Engine::GameManager::DeleteWindow(){
    window::Destroy_window(&window_setting);
}

void Engine::GameManager::LoadAsset(std::string path){
    data = AssetManager::Load_Asset(window_setting.renderer, path);
}

void Engine::GameManager::DrawObject(){
    SDL_RenderClear(window_setting.renderer);
    Animation::Render_Entity(window_setting.renderer, data, p);
    SDL_RenderPresent(window_setting.renderer);
}

void Engine::GameManager::Destroy_Object(){
    SDL_DestroyRenderer(window_setting.renderer);
    SDL_DestroyWindow(window_setting.window);
    CreateText::TTF_end();
    IMG_Quit();
    SDL_Quit();
}