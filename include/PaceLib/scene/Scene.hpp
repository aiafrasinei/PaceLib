#pragma once

#include <string>
#include <vector>
#include "TexContainer.hpp"
#include "TtfContainer.hpp"
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
  PaceLib::TexContainer *GetFontContainer();
  PaceLib::TtfContainer *GetTtfContainer();

  bool AddTex(std::filesystem::path file_path, int x, int y, int w, int h);
  bool AddFont(std::string name, std::string text, SDL_Color color);
  bool AddTtf(std::string name, std::filesystem::path file_path, int size, int style);

  SDL_Texture *GetTex(std::string name);

  SDL_Texture *GetFont(std::string name);

  TTF_Font *GetTtf(std::string name);

  void Update(SDL_Event *event);

protected:
private:
  PaceLib::TexContainer *tex_atlas;
  PaceLib::TexContainer *font_atlas;
  PaceLib::TtfContainer *ttf_atlas;

  SDL_Window *window;
  SDL_Renderer *renderer;

  std::string name;
};

} // namespace PaceLib
