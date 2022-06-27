#include "Map.h"

using namespace PaceLib;


Map::Map(std::string name, SDL_Window* window, SDL_Renderer* renderer)
{
    this->name = name;

    this->window = window;
    this->renderer = renderer; 
}

Map::~Map()
{
    
}

void Map::SetName(std::string name)
{
    this->name = name;
}


void Map::Loop(SDL_Event *e)
{

}
