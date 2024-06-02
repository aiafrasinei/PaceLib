#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Rectangle : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "rect" : ["W_2%", "H_10%", "W_7.5%", "H_3%"],
      "color" : [40, 40, 40, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the rectangle will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, PropDimColor prop);

  // end static methods

  void Draw();

 protected:
 private:
  PropDimColor prop;

  Rectangle(ShapeId sid, PropDimColor prop);
};

}
