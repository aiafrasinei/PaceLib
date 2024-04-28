#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class ButtonGrid : public Widget {
public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
    "scene" : "Default",
	  "dim" : ["H_1%", "W_1%", "W_5%", "W_5%"],
    "font" : "default",
    "distance" : 10.0
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the button will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, ButtonGridProp prop);

  // end static methods

  ButtonGridProp *GetProp() { return &prop; }

  void Draw();

  ButtonGrid();

  ~ButtonGrid();

protected:
  ButtonGridProp prop;

  ButtonGrid(ShapeId sid, ButtonGridProp inputProp);

private:
  static ButtonGridProp LoadButtonGridProp(Configuration *conf);
};

} // namespace PaceLib