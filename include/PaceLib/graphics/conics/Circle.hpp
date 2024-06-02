#pragma once

#include "DrawTypes.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Circle : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "x" : 100,
      "y" : 100,
      "radius" : 100,
      "color" : [0, 0, 0, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the cicle will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, CircleProp prop);

  // end static methods

  void SetDrawType(DrawTypes rtype);

  void Draw();

 protected:
 private:
  CircleProp prop;

  DrawTypes rtype;

  Circle(ShapeId sid, CircleProp prop);
};

}
