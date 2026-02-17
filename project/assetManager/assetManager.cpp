#include "assetManager.h"
#include "../main.h"


int main(){

    Load_Asset();

    return 0;
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

Asset Load_Asset(){
    std::string file_name;
    std::string folder_name;
    std::string path;
    Asset asset;
    for (const auto& [folder, files] : memory::Load_Action_json("project/data/asset.json").items()){
        int Imgs_count = files.size();
        std::vector<SDL_Texture*> IMGs;
        for (auto& [idx, f] : files.items()){
            file_name = f;
            folder_name = folder;
            path = "project/assets/"+folder_name+"/"+file_name;
            IMGs.push_back(Path_to_Texture(window_setting->renderer, path)); 
        }
        if (folder == "buildings") asset.buildings = IMGs;
        else if (folder == "character") asset.character = IMGs;
        else if (folder == "interactives") asset.interactives = IMGs;
        else if (folder == "tiles") asset.tiles = IMGs;
    }
}





// 일단 여기로 뺴놨는데 나중에 units.cpp 같은거 하나 만들어야될듯 2222
namespace memory{
    json Load_Action_json(const std::string path){
        std::ifstream file(path);
        json data = json::parse(file);
        return data;
    }

}