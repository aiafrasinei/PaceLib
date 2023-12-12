#include "FontContainer.hpp"
#include "ConLog.hpp"
#include "core/Window.hpp"

using namespace PaceLib;

FontContainer::FontContainer(std::string name) { this->name = name; }

FontContainer::~FontContainer() {
  for (auto pair : fnm) {
    FC_FreeFont(pair.second);
  }
  fnm.clear();
}

std::string FontContainer::GetName() { return name; }

void FontContainer::ChangeName(std::string name) { this->name = name; }

FC_Font *FontContainer::Get(std::string name) { return fnm[name]; }

void FontContainer::Remove(std::string name) {
  FC_FreeFont(fnm[name]);
  fnm.erase(name);
}

bool FontContainer::Add(std::string name, std::filesystem::path file_path,
                        int size, SDL_Color color) {
  FC_Font *font = FC_CreateFont();

  int ret = FC_LoadFont(font, Window::GetRenderer(), file_path.string().c_str(),
                        size, color, TTF_STYLE_NORMAL);

  if (ret != 1) // wtf
  {
    printf("Failed to load font");
    return false;
  } else {
    fnm[name] = font;

    ConLog::Info("Loaded font " + name +
                 " filepath: " + file_path.filename().string());
  }

  return true;
}
