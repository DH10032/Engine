#ifndef WORLD
#define WORLD

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace worldspace{
    int world[100][100] = {0}; // 대충 0 -> 기본 땅 , 나중에 알아서 바꾸쇼
}

#endif