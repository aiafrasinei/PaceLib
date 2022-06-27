#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "utils/sdlu.h"
#include "utils/SDL2/SDL_FontCache.h"
#include "TexContainer.h"


namespace PaceLib
{

    class FontContainer
    {
    public:
        FontContainer(std::string name);    
        ~FontContainer();
        
        std::string GetName();
        void ChangeName(std::string name);

        bool Add(std::string name, std::filesystem::path file_path, int size, int r, int g, int b, int a);

        bool Remove(long index);
        bool Remove(std::string name);

        FC_Font *Get(long index);
        FC_Font *Get(std::string name);
        
    protected:

    private:
        std::vector<FC_Font *> fonts;
        std::vector<std::string> fonts_names;

        std::string name;

    };
    
}
