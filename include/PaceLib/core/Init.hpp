#pragma once

#include "PaceLib.hpp"

namespace PaceLib {
class Init {
 private:
  Configuration *conf;
  Window *win;
  Root *root;

 public:
  Init();
  ~Init();

  static std::string GetVersion();

  void Loop();
  Root *GetRoot();
  Window *GetWindow();

  std::function<void(void)> onInit = nullptr;
  std::function<void(void)> onDeinit = nullptr;
  std::function<void(void)> onDraw = nullptr;
  std::function<void(void)> onUpdate = nullptr;
  std::function<void(SDL_Event *)> onEvent = nullptr;
};
}  // namespace PaceLib