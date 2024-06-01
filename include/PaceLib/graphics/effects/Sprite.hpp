#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Sprite : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "rect" : ["H_82%", "H_11%", "H_32%", "H_32%"],
      "tex_name" : "sprite_sheet.png",
      "offset" : 300,
      "nr" : 5
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string);

  // used when the sprite will have child elements
  static void BeginBlock(std::string);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, SpriteProp prop);

  // end static methods

  // setters, getters
  void SetTex(SDL_Texture *tex);
  SDL_Texture *GetTex();

  void SetOffset(int offset);
  int GetOffset();

  void SetNr(int nr);
  int GetNr();

  void Draw();
  
 protected:
 private:
  SpriteProp prop;

  SDL_FRect src_rect;
  SDL_FRect dest_rect;

  Sprite(ShapeId sid, SpriteProp inputProp);
};

}
