#pragma once

#include "Widget.hpp"

namespace PaceLib {

class Lines : public Shape {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "verts" : [ 0, 0, 10, 10, 100, 100 ]
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

  ~Lines();

 protected:
 private:
  VertsProp prop;

  Lines(ShapeId sid, VertsProp inputProp);
};

}  // namespace PaceLib
