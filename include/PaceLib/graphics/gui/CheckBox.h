#pragma once

#include "../../utils/SDL2/SDL_FontCache.h"
#include "../core/interfaces/Updateable.hpp"
#include "Label.h"
#include "Text.h"
#include "Widget.h"
#include <functional>

namespace PaceLib {

class CheckBox : public Label {
public:
  ~CheckBox();

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

  // used when the checkbox will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, LabelProp prop);

  // end static methods

  CheckBox(ShapeId sid, LabelProp prop);

  void Draw();

  void Update(SDL_Event *e);

  std::function<void(void)> onClickCallback;

  bool IsChecked();

  SDL_Color GetTextColor();

private:
  bool mouseOver;

  bool highlight;

  bool checked;

  SDL_Rect midrect;

  int textSize;

  void InternalInit();
};

} // namespace PaceLib