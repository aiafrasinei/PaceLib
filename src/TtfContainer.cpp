#include "TtfContainer.hpp"
#include "core/Window.hpp"

using namespace PaceLib;

TtfContainer::TtfContainer(std::string name) { this->name = name; }

TtfContainer::~TtfContainer() {
  for (auto pair : container) {
    TTF_CloseFont(pair.second);
  }
  container.clear();
}

std::string TtfContainer::GetName() { return name; }

void TtfContainer::ChangeName(std::string name) { this->name = name; }

TTF_Font *TtfContainer::Get(std::string name) { return container[name]; }

void TtfContainer::Remove(std::string name) {
  TTF_CloseFont(container[name]);
  container.erase(name);
}

bool TtfContainer::Add(std::string name, std::filesystem::path file_path, int size, int style) {
    TTF_Font *ttf = TTF_OpenFont(file_path.c_str(), size);

    if (ttf == nullptr) {
      SDL_Log("Failed to load font %s error: %s", file_path.filename().c_str(), TTF_GetError());
      return false;
    }

    TTF_SetFontOutline(ttf, 1);
    TTF_SetFontStyle(ttf, style);

    container[name] = ttf;
    
    return true;
}
