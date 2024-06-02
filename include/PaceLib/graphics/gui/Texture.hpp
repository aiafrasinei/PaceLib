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

  int GetWidth();
  int GetHeight();

  TextureProp *GetProp() { return &prop; }

 protected:
 private:
  TextureProp prop;

  Texture(ShapeId sid, TextureProp inputProp);
};

<<<<<<< HEAD
}  // namespace PaceLib
=======
}
>>>>>>> 68be932 (Rename dim to rect in the json configurations)
