#pragma once

#include "../../utils/SDL2/SDL_FontCache.h"
#include "../core/interfaces/Updateable.hpp"
#include "Text.h"
#include "Widget.h"
#include <functional>

namespace PaceLib {

class Label : public Widget {
public:
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

  void SetText(std::string text);
  void SetTextAlign(HorizontalAlign align);

  int GetTextSize();

  LabelProp *GetProp() { return &prop; }

  void Draw();

  Label();

  ~Label();

protected:
  LabelProp prop;

  int textSize;

  void InternalInit();

  static LabelProp LoadLabelProp(Configuration *conf);

  Label(ShapeId sid, LabelProp prop);
};

} // namespace PaceLib