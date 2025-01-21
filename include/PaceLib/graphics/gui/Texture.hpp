#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Texture : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "tex_name": "sn_yellow.png",
      "srcrect" : [],
      "dstrect" : ["700", "300", "300", "300"],
      "angle" : 0.0,
      "center" : [],
      "flip" : "none",
      "tex_access" : ""
  }
  More info:
  when "tex_name" is set to "":
    a new texture is created with pixel format RGBA8888

  using type from "tex_access" ("static", "streaming", "target")
  "" means default (set to "streaming")
  */
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the texture will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, TextureProp inputProp);

  // end static methods

  void Draw();

 // getters, setters
  void SetTex(SDL_Texture *tex);
  SDL_Texture *GetTex();

  void SetSrcRect(SDL_FRect *srcrect);
  SDL_FRect *GetSrcRect();

  void SetDstRect(SDL_FRect *dstrect);
  SDL_FRect *GetDstRect();

  void SetAngle(double angle);
  double GetAngle();

  void SetCenter(SDL_FPoint *center);
  SDL_FPoint *GetCenter();

  void SetFlip(SDL_FlipMode flip);
  SDL_FlipMode GetFlip();

 protected:
 private:
  TextureProp prop;

  Texture(ShapeId sid, TextureProp inputProp);
};

}  // namespace PaceLib
