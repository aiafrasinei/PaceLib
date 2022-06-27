#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "utils/sdlu.h"

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
        
        bool Remove(long index);
        bool Remove(std::string name);

        SDL_Texture *Get(long index);
        SDL_Texture *Get(std::string name);

        std::vector<SDL_Texture *> GetTexs();
        
        long GetNrTexs();

        void SetRect(long index, int x, int y, int w , int h);
        void SetRect(std::string name, int x, int y, int w , int h);

        SDL_Rect *GetRect(long index);
        SDL_Rect *GetRect(std::string name);

        std::string GetName();
        void ChangeName(std::string name);

    protected:

    private:
        SDL_Renderer* renderer;

        std::vector<SDL_Texture *> texs;
        std::vector<std::string> texs_names;
        std::vector<SDL_Rect *> texs_rectangles;

        std::string name;

    };
    
}
