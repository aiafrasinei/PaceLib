#include "ScrollingBackground.h"

using namespace PaceLib;

ScrollingBackground::ScrollingBackground(SDL_Texture *tex, SDL_Rect shape) {
  this->tex = tex;
  rect.x = shape.x;
  rect.y = shape.y;
  rect.w = shape.w;
  rect.h = shape.h;

  hidden = false;

  scrollingOffset = 0;
}

ScrollingBackground::~ScrollingBackground() {}

ScrollingBackground *ScrollingBackground::Begin(SDL_Texture *tex,
                                                SDL_Rect shape) {
  return new ScrollingBackground(tex, shape);
}

void ScrollingBackground::Draw(float timeStep) {
  if (!hidden) {
    scrollingOffset -= 60 * timeStep;

    if (scrollingOffset < -rect.w) {
      scrollingOffset = 0;
    }

    rect.x = scrollingOffset;
    SDL_RenderCopy(Window::GetRenderer(), tex, nullptr, &rect);
    rect.x = scrollingOffset + rect.w;
    SDL_RenderCopy(Window::GetRenderer(), tex, nullptr, &rect);
  }
}

void ScrollingBackground::SetTex(SDL_Texture *tex) { this->tex = tex; }

void ScrollingBackground::SetRect(float x, float y, float w, float h) {
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}
