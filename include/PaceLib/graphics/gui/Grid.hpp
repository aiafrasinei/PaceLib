#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Grid : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "x" : 100.0,
      "y" : 100.0,
      "nr" : 8,
      "distance" : 50.0,
      "color" : [100, 100, 100, 255]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the button will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, GridProp prop);

  // end static methods

  // setters, getters
  void SetX(int x);
  int GetX();

  void SetY(int y);
  int GetY();

  void SetDistance(int distance);
  int GetDistance();

  void SetNr(int nr);
  int GetNr();

  void SetColor(SDL_Color color);
  SDL_Color GetColor();

  void Draw();

 protected:
  GridProp prop;

  Grid(ShapeId sid, GridProp inputProp);

 private:
  static GridProp LoadGridProp(Configuration *conf);
};

}  // namespace PaceLib