#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Point : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "x" : 0,
      "y" : 0,
      "color" : [0, 0, 0, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the line will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, PointProp prop);

  // end static methods

  // setters, getters
  void SetX(int x);
  int GetX();

  void SetY(int y);
  int GetY();

  void Draw();

 protected:
 private:
  PointProp prop;

  Point(ShapeId sid, PointProp prop);
};

}
