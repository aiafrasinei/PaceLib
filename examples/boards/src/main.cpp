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
                              {(Window::width * 0.06f) + i * Window::width / 9,
                              (Window::width * 0.03f) + j * Window::width / 9,
                              (float)Window::width / 10, (float)Window::height / 10}},
                            {nullptr,
                              {(Window::width * 0.06f) + i * Window::width / 9,
                              (Window::width * 0.03f) + j * Window::width / 9,
                              (float)Window::width / 10, (float)(Window::height / 10)}},
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
                              {(Window::width * 0.06f) + i * Window::width / 10,
                              (Window::width * 0.02f) + j * Window::width / 10,
                              (float)Window::width / 11, (float)Window::height / 11}},
                            {nullptr,
                              {(Window::width * 0.06f) + i * Window::width / 10,
                              (Window::width * 0.02f) + j * Window::width / 10,
                              (float)Window::width / 11, (float)Window::height / 11}},
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
                              {(float)(Window::width * 3 / 100) + i * Window::width / 20,
                              (Window::width * 0.015f) + j * Window::width / 21,
                              (float)Window::width / 22, (float)Window::height / 22}},
                            {nullptr,
                              {(float)(Window::width * 3 / 100) + i * Window::width / 20,
                              (float)(Window::width * 0.015) + j * Window::width / 21,
                              (float)Window::width / 22, (float)Window::height / 22}},
                            {100, 100, 100, 255},
                            {0, 0, 0, 255},
                            {120, 120, 120, 255},
                            false};
          ButtonTex::Begin({root->GetCurrent(), "go_b" + std::to_string(i)}, p);
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
