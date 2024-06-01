#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Texture : public Widget {
 public:
  ~Texture();
  
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
      "flip" : "none"
  }*/
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

  void SetSrcRect(SDL_Rect *srcrect);
  SDL_Rect *GetSrcRect();

  void SetDstRect(SDL_Rect *dstrect);
  SDL_Rect *GetDstRect();

  void SetAngle(double angle);
  double GetAngle();

  void SetCenter(SDL_Point *center);
  SDL_Point *GetCenter();

  void SetFlip(SDL_RendererFlip flip);
  SDL_RendererFlip GetFlip();

 protected:
 private:
  TextureProp prop;

  Texture(ShapeId sid, TextureProp inputProp);
};

}  // namespace PaceLib
