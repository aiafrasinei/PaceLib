#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Label : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "rect" : ["H_82%", "H_11%", "W_7.5%", "H_3%"],
      "font" : "default",
      "text" : "Start",
      "text_color" : "$TEXT",
      "align" : "mid",
      "background" : "$BACKGROUND",
      "border" : "$BORDER",
      "highlight" : "$HIGHLIGHT"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the button will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, LabelProp prop);

  // end static methods

  void Draw();

  // getters, setters
  void SetText(std::string text);
  std::string GetText();

  void SetTextColor(SDL_FColor textColor);
  SDL_FColor GetTextColor();

  void SetTextAlign(HorizontalAlign align);
  HorizontalAlign GetTextAlign();

  void SetBackgroundColor(SDL_FColor backgroundColor);
  SDL_FColor GetBackgroundColor();

  void SetBorderColor(SDL_FColor borderColor);
  SDL_FColor GetBorderColor();

  void SetHighlightColor(SDL_FColor highlightColor);
  SDL_FColor GetHighlightColor();
  
  int GetTextSize();

 protected:
  LabelProp prop;

  int textSize;

  void InternalInit();

  static LabelProp LoadLabelProp(Configuration *conf);

  Label(ShapeId sid, LabelProp inputProp);
};

}