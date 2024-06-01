#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Line : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "x1" : 0,
      "y1" : 0,
      "x2" : 300,
      "y2" : 200,
      "color" : [0, 0, 0, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the line will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, LineProp prop);

  // end static methods

  // setters, getters
  void SetX1(int x1);
  int GetX1();

  void SetY1(int y1);
  int GetY1();

  void SetX2(int x2);
  int GetX2();

  void SetY2(int y2);
  int GetY2();

  void Draw();

 protected:
 private:
  LineProp prop;

  Line(ShapeId sid, LineProp inputProp);
};

}
