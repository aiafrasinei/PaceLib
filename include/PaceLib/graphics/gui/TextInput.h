#pragma once

#include "../../core/interfaces/Focusable.hpp"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Label.h"
#include "Text.h"
#include "Widget.h"

namespace PaceLib {

class TextInput : public Label, public Focusable {
public:
  // static methods

  // json configuration
  /* Loads wconf file
  example format:
  }
      "scene" : "Default",
      "dim" : ["H_82%", "H_11%", "W_7.5%", "H_3%"],
      "font" : "default",
      "text" : "",
      "text_color" : "$TEXT",
      "align" : "mid",
      "background" : "$BACKGROUND",
      "border" : "$BORDER",
      "highlight" : "$HIGHLIGHT"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the textinput will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programatic
  static void Begin(ShapeId sid, LabelProp prop);

  // end static methods

  void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void Draw();

  void Update(SDL_Event *e);

  std::string GetText();

  void SetTextColor(SDL_Color color);
  SDL_Color GetTextColor();

  ~TextInput();

private:
  int textSize;

  TextInput(ShapeId sid, LabelProp prop);

  void InternalInit();
};

} // namespace PaceLib