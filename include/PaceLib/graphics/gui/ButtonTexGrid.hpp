#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class ButtonTexGrid : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
<<<<<<< HEAD
            "dim" : ["H_1%", "W_1%", "W_5%", "W_5%"],
=======
      "rect" : ["H_1%", "W_1%", "W_5%", "W_5%"],
>>>>>>> 68be932 (Rename dim to rect in the json configurations)
      "distance" : 10.0,
      "tex_name" : "sn_yellow.png",
      "over_tex_name" : "",
      "background" : "$BACKGROUND",
      "border" : "$BORDER",
      "highlight" : "$HIGHLIGHT"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the button will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, ButtonTexGridProp prop);

  // end static methods

  // setters, getters
  void SetScene(std::string scene);
  std::string GetScene();

  void SetDistance(int distance);
  int GetDistance();

  void SetNormal(TexProp normal);
  TexProp GetNormal();

  void SetOver(TexProp over);
  TexProp GetOver();

  void SetBackgroundColor(SDL_Color color);
  SDL_Color GetBackgroundColor();

  void SetBorderColor(SDL_Color color);
  SDL_Color GetBorderColor();

  void SetHighlightColor(SDL_Color color);
  SDL_Color GetHighlightColor();

  void SetDrawBorder(bool drawBorder);
  bool GetDrawBorder();

  void Draw();

 protected:
  ButtonTexGridProp prop;

  ButtonTexGrid(ShapeId sid, ButtonTexGridProp inputProp);

 private:
  static ButtonTexGridProp LoadButtonTexGridProp(Configuration *conf);
};

}