#pragma once

#include "../config/Configuration.hpp"
#include "../utils/Platform.hpp"

namespace PaceLib {

class Window {
 public:
  Window(Configuration *conf);
  ~Window();

  static SDL_Renderer *GetRenderer();
  static SDL_Window *GetWindow();

  void Clear();
  void Present();
  void Close();

  static void SetDrawColor(SDL_FColor col);

  static void SetBackgroundColor(SDL_FColor col);

  static SDL_FColor GetBackgroundColor();

  static bool running;

  static int width, height;

 private:
  static SDL_Renderer *renderer;
  static SDL_Window *window;

  static SDL_FColor backgroundColor;

  bool success;

 protected:
};

}