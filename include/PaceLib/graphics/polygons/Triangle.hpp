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

  void SetColor(SDL_FColor color);

  void Draw();

  TriangleProp *GetProp() { return &prop; }

  ~Triangle();

protected:
private:
  TriangleProp prop;

  SDL_Point points[4];

  SDL_Vertex verts[3];

  Triangle(ShapeId sid, TriangleProp prop);
};

} // namespace PaceLib
