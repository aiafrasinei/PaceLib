#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class ButtonTexGrid : public Widget {
public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
	    "dim" : ["H_1%", "W_1%", "W_5%", "W_5%"],
      "distance" : 10.0,
      "tex_name" : "sn_yellow.png",
      "over_tex_name" : "",
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
  static void Begin(ShapeId sid, ButtonTexGridProp prop);

  // end static methods

  ButtonTexGridProp *GetProp() { return &prop; }

  void Draw();

  ButtonTexGrid();

  ~ButtonTexGrid();

protected:
  ButtonTexGridProp prop;

  ButtonTexGrid(ShapeId sid, ButtonTexGridProp inputProp);

private:
  static ButtonTexGridProp LoadButtonTexGridProp(Configuration *conf);
};

} // namespace PaceLib