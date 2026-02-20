#include "assetManager.h"


namespace AssetManager{
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
    
    Asset Load_Asset(SDL_Renderer* renderer, std::string path){
        std::string file_name;
        std::string folder_name;

        std::ifstream file(path);
        json data = json::parse(file);

        Asset asset;
        for (const auto& [folder, files] : data.items()){
            int Imgs_count = files.size();
            std::vector<SDL_Texture*> IMGs;
            for (auto& [idx, f] : files.items()){
                file_name = f;
                folder_name = folder;
                path = "Game/assets/img/"+folder_name+"/"+file_name;
                IMGs.push_back(Path_to_Texture(renderer, path)); 
            }
            if (folder == "buildings") asset.buildings = IMGs;
            else if (folder == "character") asset.character = IMGs;
            else if (folder == "interactives") asset.interactives = IMGs;
            else if (folder == "tiles") asset.tiles = IMGs;
        }
        return asset;
    }
}