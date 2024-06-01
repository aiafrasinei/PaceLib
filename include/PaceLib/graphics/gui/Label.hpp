#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Label : public Widget {
 public:
  Label();
  
  ~Label();

  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "dim" : ["H_82%", "H_11%", "W_7.5%", "H_3%"],
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

  void SetTextColor(SDL_Color textColor);
  SDL_Color GetTextColor();

  void SetTextAlign(HorizontalAlign align);
  HorizontalAlign GetTextAlign();

  void SetBackgroundColor(SDL_Color backgroundColor);
  SDL_Color GetBackgroundColor();

  void SetBorderColor(SDL_Color borderColor);
  SDL_Color GetBorderColor();

  void SetHighlightColor(SDL_Color highlightColor);
  SDL_Color GetHighlightColor();
  
  int GetTextSize();

 protected:
  LabelProp prop;

  int textSize;

  void InternalInit();

  static LabelProp LoadLabelProp(Configuration *conf);

  Label(ShapeId sid, LabelProp inputProp);
};

}  // namespace PaceLib