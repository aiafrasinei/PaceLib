#pragma once

#include "SDL3/SDL.h"

class Updateable {

public:
  virtual void Update(SDL_Event *e) = 0;

};