#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include "TexContainer.hpp"
#include "utils/Platform.hpp"
#include "utils/SDL2/SDL_FontCache.h"

namespace PaceLib {

class FontContainer {
public:
  FontContainer(std::string name);
  ~FontContainer();

  bool Add(std::string name, std::filesystem::path file_path, int size,
           SDL_Color color);

  void Remove(std::string name);

  FC_Font *Get(std::string name);

  std::string GetName();
  void ChangeName(std::string name);

protected:
private:
  std::map<std::string, FC_Font *> fnm;
  std::string name;
};

} // namespace PaceLib
