#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Props.hpp"
#include "utils/Platform.hpp"

namespace PaceLib {

class TexContainer {
 public:
  TexContainer(std::string name, SDL_Renderer *renderer);
  ~TexContainer();

  bool Add(std::filesystem::path file_path);
  bool Add(std::string name, SDL_Texture *tex);
  bool Add(std::filesystem::path file_path, int x, int y, int w, int h);

  void Remove(std::string name);

  SDL_Texture *Get(std::string name);

  SDL_FRect *GetRect(std::string name);

  long GetNrTexs();

  void SetRect(std::string name, int x, int y, int w, int h);

  std::string GetName();
  void ChangeName(std::string name);

 protected:
 private:
  SDL_Renderer *renderer;

  std::map<std::string, TexProp *> ntr;
  std::string name;

  SDL_Texture *LoadTexture(SDL_Renderer *renderer, std::string path);
};

}
