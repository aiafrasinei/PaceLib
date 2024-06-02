#pragma once

#include "SDL3/SDL.h"

namespace PaceLib {

class Drawable {

public:
  virtual void Draw() = 0;

};

}