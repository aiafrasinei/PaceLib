#include "TtfContainer.hpp"
#include "core/Window.hpp"

using namespace PaceLib;

TtfContainer::TtfContainer(std::string name) { this->name = name; }

TtfContainer::~TtfContainer() {
  //for (auto pair : fnm) {
  //  FC_FreeFont(pair.second);
  //}
  container.clear();
}

std::string TtfContainer::GetName() { return name; }

void TtfContainer::ChangeName(std::string name) { this->name = name; }

TTF_Font *TtfContainer::Get(std::string name) { return container[name]; }

void TtfContainer::Remove(std::string name) {
  //FC_FreeFont(fnm[name]);
  container.erase(name);
}

bool TtfContainer::Add(std::string name, std::filesystem::path file_path,
                        int size, SDL_Color color) {

  return true;
}
