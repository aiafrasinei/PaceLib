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
      "tex_name": "tex.png",
      "dim" : "[10, 10, 100 , 100]"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the texture will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, TexProp inputProp);

  // end static methods

  void Draw();

  int GetWidth();
  int GetHeight();

  TexProp *GetProp() { return &prop; }

 protected:
 private:
  TexProp prop;

  Texture(ShapeId sid, TexProp inputProp);
};

}  // namespace PaceLib
