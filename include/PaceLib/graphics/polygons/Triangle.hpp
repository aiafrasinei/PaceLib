#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Triangle : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "x1" : 0,
      "y1" : 0,
      "x2" : 150,
      "y2" : 0,
      "x3" : 150,
      "y3" : 150,
      "color" : [40, 40, 40, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the triangle will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, TriangleProp prop);

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

  void SetX3(int x3);
  int GetX3();

  void SetY3(int y3);
  int GetY3();

  void Draw();

 protected:
 private:
  TriangleProp prop;

  SDL_Point points[4];

  SDL_Vertex verts[3];

  Triangle(ShapeId sid, TriangleProp inputProp);
};

}  // namespace PaceLib
