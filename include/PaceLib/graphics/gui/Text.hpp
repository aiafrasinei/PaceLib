#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Text : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "pos" : ["W_1%", "W_0.6%"],
      "font" : "default",
      "text" : "Text text text",
      "color" : [140, 140, 140, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the text will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programatic

  static void Begin(ShapeId sid, TextProp prop);

  // end static methods

  void Draw();

  int GetWidth();
  int GetHeight();

  void SetX(int x);
  void SetY(int y);

  std::string GetText();
  void SetText(std::string text);

  TextProp *GetProp() { return &prop; }

  ~Text();

 protected:
 private:
  TextProp prop;

  static TextProp LoadTextProp(Configuration *conf);

  Text(ShapeId sid, TextProp prop);
};

}  // namespace PaceLib
