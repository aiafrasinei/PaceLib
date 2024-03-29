#pragma once

#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "Widget.h"

namespace PaceLib {

class TextArea : public Widget {
public:
  ~TextArea();

  // static methods

  // json configuration

  /* Loads wconf file
  {
      "scene" : "Default",
      "dim" : ["W_1%", "H_11%", "W_10%", "H_14%"],
      "font" : "default",
      "text_arr" : [ "first", "second line", "third line"],
      "text_color" : "$TEXT",
      "background" : "$BACKGROUND",
      "border" : "$BORDER"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the textarea will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programatic
  static void Begin(ShapeId sid, MultiItemsProp prop);

  // end static methods

  void SetTextSpacing(int size);

  void Draw();

  MultiItemsProp *GetProp() { return &prop; }

private:
  MultiItemsProp prop;

  int textSpacing;

  TextArea(ShapeId sid, MultiItemsProp prop);

  static MultiItemsProp LoadTextAreaProp(Configuration *conf);

  void InternalInit();
};

} // namespace PaceLib