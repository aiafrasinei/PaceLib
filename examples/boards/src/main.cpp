#define SDL_MAIN_HANDLED
#include "core/Init.hpp"

using namespace PaceLib;

Init *starter = nullptr;

bool init() {
  Root *root = starter->GetRoot();

  Tabber::BeginBlock("Bag");
  Tabber::BeginTabBlock("Chess");
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      ButtonTexProp p = {{nullptr,
                          {(Window::width * 0.06) + i * Window::width / 9,
                           (Window::width * 0.03) + j * Window::width / 9,
                           Window::width / 10, Window::height / 10}},
                         {nullptr,
                          {(Window::width * 0.06) + i * Window::width / 9,
                           (Window::width * 0.03) + j * Window::width / 9,
                           Window::width / 10, Window::height / 10}},
                         {100, 100, 100, 255},
                         {0, 0, 0, 255},
                         {120, 120, 120, 255},
                         false};
      ButtonTex::Begin({root->GetCurrent(), "chess_b" + i}, p);
    }
  }
  Tabber::EndTabBlock();

  Tabber::BeginTabBlock("Shogi");
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      ButtonTexProp p = {{nullptr,
                          {(Window::width * 0.06) + i * Window::width / 10,
                           (Window::width * 0.02) + j * Window::width / 10,
                           Window::width / 11, Window::height / 11}},
                         {nullptr,
                          {(Window::width * 0.06) + i * Window::width / 10,
                           (Window::width * 0.02) + j * Window::width / 10,
                           Window::width / 11, Window::height / 11}},
                         {100, 100, 100, 255},
                         {0, 0, 0, 255},
                         {120, 120, 120, 255},
                         false};
      ButtonTex::Begin({root->GetCurrent(), "shogi_b" + i}, p);
    }
  }
  Tabber::EndTabBlock();

  Tabber::BeginTabBlock("Go");
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 19; j++) {
      ButtonTexProp p = {{nullptr,
                          {(Window::width * 3 / 100) + i * Window::width / 20,
                           (Window::width * 0.015) + j * Window::width / 21,
                           Window::width / 22, Window::height / 22}},
                         {nullptr,
                          {(Window::width * 3 / 100) + i * Window::width / 20,
                           (Window::width * 0.015) + j * Window::width / 21,
                           Window::width / 22, Window::height / 22}},
                         {100, 100, 100, 255},
                         {0, 0, 0, 255},
                         {120, 120, 120, 255},
                         false};
      ButtonTex::Begin({root->GetCurrent(), "go_b" + i}, p);
    }
  }
  Tabber::EndTabBlock();
  Tabber::EndBlock();

  return true;
}

int main(int argc, const char *argv[]) {
  starter = new Init();

  starter->onInit = &init;

  starter->Loop();

  return 0;
}
