#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {
  
class Hotspot : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "rect" : ["W_25%", "W_3%", "W_20%", "W_22%"],
      "background" : [80, 70, 80, 255],
      "type" : "rect",
      "texture" : ""
  }
  More info:
  "texture" : "" means do not use a texture
  "type" can be: "rect", "filled", "texture"
  */
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the hotspot will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic

  static void Begin(ShapeId sid, HotspotProp prop);

  // end static methods

  // setters, getters
  void SetBackgroundColor(SDL_Color backgroundColor);
  SDL_Color GetBackgroundColor();

  void SetHover(Hover type);
  Hover GetHover();

  void SetTex(SDL_Texture *tex);
  SDL_Texture *GetTex();

  void SetHighlight(bool state);

  void SetHighlightColor(SDL_Color color);

  void Draw();

  void Update(SDL_Event *e);

 private:
  Hotspot(ShapeId sid, HotspotProp inputProp);

  HotspotProp prop;

  bool mouseOver;

  bool isHighlight;

  SDL_Color highlightColor;

  SDL_Texture *tex;

  static HotspotProp LoadHotspotProp(Configuration *conf);
};

}