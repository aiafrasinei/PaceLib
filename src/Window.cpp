#include "Window.hpp"
#include "utils/ConLog.hpp"

using namespace std;

SDL_Renderer *Window::renderer = nullptr;
SDL_Window *Window::window = nullptr;
SDL_Color Window::backgroundColor = {50, 50, 50, 255};
bool Window::running = true;
int Window::width = -1;
int Window::height = -1;

Window::Window(Configuration *conf) {
  success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    ConLog::Error("SDL could not initialize! SDL Error: " +
                  string(SDL_GetError()));
    success = false;
  } else {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      ConLog::Warn("Linear texture filtering not enabled!");
    }

    std::string title = conf->Get("Title").get<std::string>();
    if (conf->Get("Fullscreen") == 0) {
      window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, conf->Get("Width"),
                                conf->Get("Height"), SDL_WINDOW_SHOWN);
    } else if (conf->Get("Fullscreen") == 1) {
      window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, conf->Get("Width"),
                                conf->Get("Height"), SDL_WINDOW_FULLSCREEN);
    } else if (conf->Get("Fullscreen") == 2) {
      window =
          SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, conf->Get("Width"),
                           conf->Get("Height"), SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    if (window == nullptr) {
      ConLog::Error("Window could not be created! SDL Error: " +
                    string(SDL_GetError()));
      success = false;
    } else {
      ConLog::Info("Window created");

      width = conf->Get("Width");
      height = conf->Get("Height");

      if (conf->Get("Vsync") == "0") {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      } else {
        renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      }

      if (renderer == nullptr) {
        ConLog::Error("Renderer could not be created! SDL Error: " +
                      string(SDL_GetError()));
        success = false;
      } else {
        ConLog::Info("Renderer created");
        SDL_SetRenderDrawColor(
            Window::GetRenderer(), Window::GetBackgroundColor().r,
            Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,
            Window::GetBackgroundColor().a);

        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags)) {
          ConLog::Error("SDL_image could not initialize! SDL_image Error: " +
                        string(IMG_GetError()));
          success = false;
        }

        if (TTF_Init() == -1) {
          ConLog::Error("SDL_ttf could not initialize! SDL_ttf Error: " +
                        string(TTF_GetError()));
          success = false;
        }
      }
    }
  }

  if (success) {
    ConLog::Info("Subsystems initialized");
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

void Window::SetDrawColor(SDL_Color col) {
  SDL_SetRenderDrawColor(Window::GetRenderer(), col.r, col.g, col.b, col.a);
}

void Window::SetBackgroundColor(SDL_Color col) {
  backgroundColor.r = col.r;
  backgroundColor.g = col.g;
  backgroundColor.b = col.b;
  backgroundColor.a = col.a;

  SetDrawColor(backgroundColor);
}

SDL_Color Window::GetBackgroundColor() { return backgroundColor; }
