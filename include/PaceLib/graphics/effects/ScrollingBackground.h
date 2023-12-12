#pragma once

#include "../../core/Window.hpp"
#include "../../core/interfaces/Hidable.hpp"
#include "../../utils/Platform.h"
#include <string>
#include <vector>

namespace PaceLib {

class ScrollingBackground : public Hidable {
public:
  ScrollingBackground(SDL_Texture *tex, SDL_Rect shape);
  ~ScrollingBackground();

  static ScrollingBackground *Begin(SDL_Texture *tex, SDL_Rect shape);

  void SetTex(SDL_Texture *tex);
  void SetRect(float x, float y, float w, float h);

  void Draw(float timeStep);

protected:
private:
  SDL_Texture *tex;
  SDL_Rect rect;

  float scrollingOffset;
};

} // namespace PaceLib
