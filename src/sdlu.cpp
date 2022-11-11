#include "sdlu.h"
#include "utils/ConLog.hpp"


SDL_Texture* load_texture(SDL_Renderer* renderer, std::string path)
{
    SDL_Texture* new_tex = nullptr;

    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if(loaded_surface == nullptr)
    {
		ConLog::Error("Unable to load image " + path + "! SDL_image Error: " + IMG_GetError());
    }
    else
    {
        new_tex = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(new_tex == nullptr)
        {
			ConLog::Error("Unable to create texture from " + path + "! SDL Error: " + SDL_GetError());
        } else {
			ConLog::Info("Loaded " + path);
		}

        SDL_FreeSurface(loaded_surface);
    }

    return new_tex;
}
