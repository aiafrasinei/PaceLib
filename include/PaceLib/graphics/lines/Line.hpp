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

  void Draw();
<<<<<<< HEAD

  LineProp *GetProp() { return &prop; }

  ~Line();

=======
  
>>>>>>> 0d59a85 (Fix TextInput not printing key input, default constructors/destructors)
 protected:
 private:
  LineProp prop;

  Line(ShapeId sid, LineProp prop);
};

}  // namespace PaceLib
