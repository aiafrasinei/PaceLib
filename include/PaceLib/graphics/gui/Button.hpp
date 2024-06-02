#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Label.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Button : public Label {
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

  void SetHighlight(bool state);

  void Draw();
  
  void Update(SDL_Event *e);

<<<<<<< HEAD
  LabelProp *GetProp() { return &prop; }

  ~Button();

=======
>>>>>>> 0d59a85 (Fix TextInput not printing key input, default constructors/destructors)
 private:
  bool mouseOver;

  bool highlight;

  Button(ShapeId sid, LabelProp inputProp);
};

}