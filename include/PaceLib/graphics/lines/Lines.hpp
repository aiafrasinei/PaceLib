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
  static void Begin(ShapeId sid, std::vector<SDL_Point> verts);

  // end static methods
  void Draw();

  ~Lines();

protected:
private:
  std::vector<SDL_Point> verts;

  Lines(ShapeId sid, std::vector<SDL_Point> verts);
};

} // namespace PaceLib
