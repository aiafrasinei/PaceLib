#include "Init.hpp"

using namespace PaceLib;

Init::Init() {
  ConLog::Info("PaceLib " + Init::GetVersion() + " start\n");

  conf = new Configuration("conf.json");

  win = new Window(conf);

  root = &Root::GetInstance();
  root->SetCurrent(root);
}

Init::~Init() {
  ConLog::Info("End");
  for (auto item : root->GetScenes()) {
    delete item.second;
  }

  delete conf;
  delete win;
}

Root *Init::GetRoot() { return root; }

Window *Init::GetWindow() { return win; }

void Init::Loop() {
  ConLog::Info("Init callback");
  if (onInit != nullptr)
    onInit();

  SDL_Event e;
  while (Window::running) {
    if (onUpdate != nullptr)
      onUpdate();

    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        Window::running = false;
      }

      if (onEvent != nullptr)
        onEvent(&e);

      root->Update(&e);
    }

    win->Clear();

    if (onDraw != nullptr)
      onDraw();

    root->Draw();

    win->Present();
  }

  ConLog::Info("Deinit callback");
  if (onDeinit != nullptr)
    onDeinit();

  delete this;
}

std::string Init::GetVersion() {
  return std::to_string(PACELIB_MAJOR_VERSION) + "." +
         std::to_string(PACELIB_MINOR_VERSION) + "." +
         std::to_string(PACELIB_PATCHLEVEL);
}
