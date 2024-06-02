#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class ButtonTex : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "rect" : ["W_47%", "H_16%", "H_5%", "H_5%"],
      "tex_name" : "sn_yellow.png",
      "over_tex_name" : "",
      "background" : "$BACKGROUND",
      "border" : "$BORDER",
      "highlight" : "$HIGHLIGHT"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the buttontex will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, ButtonTexProp prop);

  // end static methods

  // getters, setters
  void SetNormal(TexProp normal);
  TexProp GetNormal();

  void SetOver(TexProp over);
  TexProp GetOver();

  void SetBackgroundColor(SDL_Color backgroundColor);
  SDL_Color GetBackgroundColor();

  void SetBorderColor(SDL_Color borderColor);
  SDL_Color GetBorderColor();

  void SetHighlightColor(SDL_Color highlightColor);
  SDL_Color GetHighlightColor();

  bool drawBorder;

  void SetBorder(bool state);
  
  void SetHighlight(bool state);

  void Draw();

  void Update(SDL_Event *e);

 private:
  bool mouseOver;

  bool highlight;

  ButtonTexProp prop;

  static ButtonTexProp LoadButtonTexProp(Configuration *conf);

  ButtonTex(ShapeId sid, ButtonTexProp prop);
};

}