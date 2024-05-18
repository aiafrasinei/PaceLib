#pragma once

#include "Widget.hpp"

namespace PaceLib {
class Tex : public Hidable {
 public:
  Tex(std::string path, int x, int y);
  Tex(std::string path, int x, int y, int w, int h);

  Tex(SDL_Texture *tex, int x, int y);
  Tex(SDL_Texture *tex, int x, int y, int w, int h);

  ~Tex();

  void Free();

  void Draw(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
            SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void SetColor(Uint8 r, Uint8 g, Uint8 b);
  void SetBlendMode(SDL_BlendMode blending);
  void SetAlpha(Uint8 a);

  int GetWidth();
  int GetHeight();

 protected:
 private:
  SDL_Texture *tex;
  SDL_Rect rect;
};

class Texture : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "tex_name": "tex.png",
      "dim" : [10, 10, 100 , 100]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the texture will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programatic

  static void Begin(ShapeId sid, SDL_Texture *tex, int x, int y);
  static void Begin(ShapeId sid, SDL_Texture *tex, SDL_Rect dim);

  // end static methods

  void Draw();

  void SetColor(Uint8 r, Uint8 g, Uint8 b);
  void SetBlendMode(SDL_BlendMode blending);
  void SetAlpha(Uint8 a);

  int GetWidth();
  int GetHeight();

  ~Texture();

 protected:
 private:
  SDL_Texture *tex;
  SDL_Rect rect;

  Tex *ctex;

  Texture(ShapeId sid, SDL_Texture *tex, SDL_Rect dim);
};

}  // namespace PaceLib
