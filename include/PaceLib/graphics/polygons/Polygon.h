#pragma once

#include "Widget.h"

namespace PaceLib {

class Polygon : public Shape {
public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "verts" : [ 0, 0, 10, 10, 100, 100 ]
      "colors" : [ 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255 ]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the polygon will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, std::vector<SDL_Vertex> verts);

  // end static methods

  void Draw();

  ~Polygon();

protected:
private:
  std::vector<SDL_Vertex> verts;

  Polygon(ShapeId sid, std::vector<SDL_Vertex> verts);
};

} // namespace PaceLib
