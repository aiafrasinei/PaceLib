#pragma once

#include "Label.hpp"
#include "Text.hpp"

namespace PaceLib {

class Tooltip : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  {
      "scene" : "Default",
      "font" : "default",
      "text" : "this is a color label",
      "text_color" : "$TEXT",
      "align" : "mid",
      "color" : [70, 80, 90, 255],
      "border" : [70, 80, 90, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the tooltip will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, TooltipProp prop);

  // end static methods

  void SetText(std::string text);
  std::string GeText();

  void SetTextColor(SDL_Color color);
  SDL_Color GetTextColor();

  void SetBorderColor(SDL_Color color);
  SDL_Color GetBorderColor();

  void Draw();

 private:
  TooltipProp prop;

  int textSize;

  Tooltip(ShapeId sid, TooltipProp prop);

  void InternalInit();

  static TooltipProp LoadTooltipProp(Configuration *conf);
};

}