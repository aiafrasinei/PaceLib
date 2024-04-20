#pragma once

#include "Button.hpp"
#include "ButtonTex.hpp"
#include "Label.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Tab : public Widget {
public:
  ~Tab();

  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "dim" : ["W_25%", "W_3%", "W_20%", "W_22%"],
      "background" : [80, 70, 80, 255]
      "border : [0, 0, 0, 255]"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the tab will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, TabProp prop);

  // end static methods

  Tab(ShapeId sid, TabProp prop);

  void Draw();

  void Add(Shape *s);

  void Update(SDL_Event *e);

  TabProp *GetProp() { return &prop; }
  
  Button *GetButton(std::string child);
  ButtonTex *GetButtonTex(std::string child);
  Label *GetLabel(std::string child);
  Widget *GetWidget(std::string child);

private:
  TabProp prop;

  static TabProp LoadTabProp(Configuration *conf);
};

} // namespace PaceLib