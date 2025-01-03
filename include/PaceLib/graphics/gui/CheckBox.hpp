#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Label.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class CheckBox : public Label {
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

  // used when the checkbox will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, LabelProp prop);

  // end static methods

  CheckBox(ShapeId sid, LabelProp prop);

  void Draw();

  void Update(SDL_Event *e);

  bool IsChecked();

 private:
  bool mouseOver;

  bool highlight;

  bool checked;

  SDL_FRect midrect;

  int textSize;

  void InternalInit();
};

}