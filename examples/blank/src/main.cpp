#define SDL_MAIN_HANDLED
#include "Init.hpp"

using namespace PaceLib;

Init *starter = nullptr;

void draw() { Window::SetBackgroundColor({10, 10, 90}); }

int main(int argc, const char *argv[]) {
  starter = new Init();

  starter->onDraw = &draw;

  starter->Loop();

  return 0;
}
