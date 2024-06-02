#pragma once

#include "SDL2/SDL.h"

namespace PaceLib {

class Updateable {
 public:
  virtual void Update(SDL_Event *e) = 0;

 private:
 protected:
};

}