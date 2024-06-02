#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Grid : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
    "x" : 100.0,
          "y" : 100.0,
    "nr" : 8,
    "distance" : 50.0,
    "color" : [100, 100, 100, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the button will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, GridProp prop);

  // end static methods

  GridProp *GetProp() { return &prop; }

  void Draw();

  Grid();

  ~Grid();

 protected:

 private:
  static GridProp LoadGridProp(Configuration *conf);

  GridProp prop;

  Grid(ShapeId sid, GridProp inputProp);
};

}  // namespace PaceLib