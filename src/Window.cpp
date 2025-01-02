#include "Window.hpp"

using namespace PaceLib;

SDL_Renderer *Window::renderer = nullptr;
SDL_Window *Window::window = nullptr;
SDL_FColor Window::backgroundColor = {50, 50, 50, 255};
bool Window::running = true;
int Window::width = -1;
int Window::height = -1;

Window::Window(Configuration *conf) {
  success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
    success = false;
  } else {
    std::string title = conf->Get("Title").get<std::string>();
    if (conf->Get("Fullscreen") == 0) {
      window = SDL_CreateWindow(title.c_str(), conf->Get("Width"),
                                conf->Get("Height"), 0);
    } else if (conf->Get("Fullscreen") == 1) {
      window = SDL_CreateWindow(title.c_str(), conf->Get("Width"),
                                conf->Get("Height"), SDL_WINDOW_FULLSCREEN);
    }

    if (window == nullptr) {
      SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
      success = false;
    } else {
      SDL_Log("Window created");

      width = conf->Get("Width");
      height = conf->Get("Height");

      if (conf->Get("Vsync") == "0") {
        renderer = SDL_CreateRenderer(window, NULL);
      } else {
        renderer = SDL_CreateRenderer(window, NULL);
      }

      if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL Error: %s", SDL_GetError());
        success = false;
      } else {
        SDL_Log("Renderer created");
        SDL_SetRenderDrawColor(
            Window::GetRenderer(), Window::GetBackgroundColor().r,
            Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,
            Window::GetBackgroundColor().a);

        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags)) {
          SDL_Log("SDL_image could not initialize! SDL_image Error: %s",
                  IMG_GetError());
          success = false;
        }

        if (TTF_Init() == -1) {
          SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s",
                  TTF_GetError());
          success = false;
        }
      }
    }
  }

  if (success) {
    SDL_Log("Subsystems initialized");
  }
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = nullptr;
  renderer = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  success = false;
  running = false;
}

SDL_Renderer *Window::GetRenderer() { return renderer; }

SDL_Window *Window::GetWindow() { return window; }

void Window::Clear() { SDL_RenderClear(renderer); }

void Window::Present() { SDL_RenderPresent(renderer); }

void Window::SetDrawColor(SDL_FColor col) {
  SDL_SetRenderDrawColor(Window::GetRenderer(), col.r, col.g, col.b, col.a);
}

void Window::SetBackgroundColor(SDL_FColor col) {
  backgroundColor.r = col.r;
  backgroundColor.g = col.g;
  backgroundColor.b = col.b;
  backgroundColor.a = col.a;

  SetDrawColor(backgroundColor);
}

SDL_FColor Window::GetBackgroundColor() { return backgroundColor; }
