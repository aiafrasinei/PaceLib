#pragma once

#include <string>
#include <vector>
#include "Scene.hpp"
#include "utils/Platform.h"

namespace PaceLib
{

    class Place
    {
    public:
        Place(std::string name, SDL_Window* window, SDL_Renderer* renderer);    
        ~Place();
        
        void SetName(std::string name);

        void Loop(SDL_Event *event);

    protected:

    private:
        std::vector<PaceLib::Scene> *scenes;

        SDL_Window* window;
        SDL_Renderer* renderer;

        std::string name;

    };

}
