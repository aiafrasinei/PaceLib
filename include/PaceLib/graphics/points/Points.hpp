#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Points : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "verts" : [ 0, 0, 10, 10, 100, 100 ],
      "color" : [0, 0, 0, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the polygon will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, VertsProp prop);

  // end static methods

  // setters, getters
  void SetVerts(std::vector<SDL_Point> verts);
  std::vector<SDL_Point> GetVerts();

  void Draw();
  
 protected:
 private:
  VertsProp prop;

  Points(ShapeId sid, VertsProp inputProp);
};

}  // namespace PaceLib
