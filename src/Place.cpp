#include "Place.hpp"

using namespace PaceLib;

Place::Place(std::string name, SDL_Window *window, SDL_Renderer *renderer) {
  this->name = name;

  this->window = window;
  this->renderer = renderer;
}

Place::~Place() {}

void Place::SetName(std::string name) { this->name = name; }

void Place::Loop(SDL_Event *e) {}
