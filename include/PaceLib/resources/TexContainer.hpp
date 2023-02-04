#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "utils/Platform.h"
#include "Props.h"
#include <map>


namespace PaceLib
{

    class TexContainer
    {
    public:
        TexContainer(std::string name, SDL_Renderer* renderer);    
        ~TexContainer();
        
        bool Add(std::filesystem::path file_path);
        bool Add(std::string name, SDL_Texture *tex);
        bool Add(std::filesystem::path file_path, int x, int y, int w , int h);
        
        void Remove(std::string name);

        SDL_Texture *Get(std::string name);
        
        SDL_Rect *GetRect(std::string name);

        long GetNrTexs();

        void SetRect(std::string name, int x, int y, int w , int h);

        std::string GetName();
        void ChangeName(std::string name);

    protected:

    private:
        SDL_Renderer* renderer;

        std::map<std::string, TexProp *> ntr;
        std::string name;

        SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
    };
    
}
