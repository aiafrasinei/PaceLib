#define SDL_MAIN_HANDLED
#include "Init.hpp"

using namespace PaceLib;

Init *starter = nullptr;

SDL_Renderer *renderer = nullptr;

SDL_Vertex *v = nullptr;

void init() {
  renderer = starter->GetWindow()->GetRenderer();

  v = new SDL_Vertex[3];

  v[0].position.x = 400;
  v[0].position.y = 150;
  v[0].color = {255, 0, 0, 255};

  v[1].position.x = 200;
  v[1].position.y = 450;
  v[1].color = {0, 0, 255, 255};

  v[2].position.x = 600;
  v[2].position.y = 450;
  v[2].color = {0, 255, 0, 255};
}

void draw() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderGeometry(renderer, nullptr, v, 3, nullptr, 0);
  SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
}

int main(int argc, const char *argv[]) {
  starter = new Init();

  starter->onInit = &init;
  starter->onDraw = &draw;

  starter->Loop();

  return 0;
}
