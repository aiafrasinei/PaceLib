#pragma once

#include "../../utils/SDL2/SDL_FontCache.h"
#include "../core/interfaces/Updateable.hpp"
#include "Label.h"
#include "Text.h"
#include "Widget.h"
#include <functional>

namespace PaceLib {

class Button : public Label {
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

  void SetHighlight(bool state);

  std::function<void(void)> onClickCallback;

  void Draw();
  void Update(SDL_Event *e);

  ~Button();

private:
  bool mouseOver;

  bool highlight;

  Button(ShapeId sid, LabelProp prop);
};

} // namespace PaceLib