#pragma once

#include <string>
#include <vector>
#include "FontContainer.hpp"
#include "TexContainer.hpp"
#include "core/interfaces/Drawable.hpp"
#include "utils/Platform.hpp"

namespace PaceLib {

class Scene : public Drawable {
public:
  Scene(std::string name, SDL_Window *window, SDL_Renderer *renderer);
  ~Scene();

  void Start();
  void Draw();
  void Stop();

  std::string GetName();
  void SetName(std::string name);

  PaceLib::TexContainer *GetTexContainer();
  PaceLib::FontContainer *GetFontContainer();

  bool AddTex(std::filesystem::path file_path, int x, int y, int w, int h);
  bool AddFont(std::string name, std::filesystem::path file_path, int size,
               SDL_Color color);

  SDL_Texture *GetTex(std::string name);

  FC_Font *GetFont(std::string name);

  void Update(SDL_Event *event);

protected:
private:
  PaceLib::TexContainer *tex_atlas;
  PaceLib::FontContainer *font_atlas;

  SDL_Window *window;
  SDL_Renderer *renderer;

  std::string name;
};

} // namespace PaceLib
