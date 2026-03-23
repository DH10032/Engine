#include "GameManager.h"



void Engine::GameManager::ShowWindow(){
    window::Create_window(&window_setting, SDL_WINDOW_SHOWN);
    CreateText::TTF_start(window_setting.renderer);
}

void Engine::GameManager::DeleteWindow(){
    window::Destroy_window(&window_setting);
}

void Engine::GameManager::LoadAsset(std::string path){
    data = AssetManager::Load_Asset(window_setting.renderer, path);
}

void Engine::GameManager::DrawObject(DenseComponentPool<Parts>& action_buffer){
    HAL::RenderClear(window_setting.renderer);
    GameGraphicApi::Render_Entity(window_setting.renderer, data, action_buffer);
    HAL::RenderPresent(window_setting.renderer);
}

void Engine::GameManager::Destroy_window(){
    HAL::Destroy(window_setting);
    CreateText::TTF_end();
}