#pragma once

#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class TextArea : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  {
      "scene" : "Default",
      "dim" : ["W_1%", "H_11%", "W_10%", "H_14%"],
      "font" : "default",
      "text_arr" : [ "first", "second line", "third line"],
      "text_color" : "$TEXT",
      "background" : "$BACKGROUND",
      "border" : "$BORDER"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the textarea will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programatic
  static void Begin(ShapeId sid, MultiItemsProp prop);

  // end static methods

  void SetTextSpacing(int size);

  void Draw();

  // getters, setters
  void SetScene(std::string scene);
  std::string GetScene();

  void SetFont(std::string font);
  std::string GetFont();

  void SetText(std::vector<std::string> tarr);
  std::vector<std::string> GetText();

  void SetTextColor(SDL_Color color);
  SDL_Color GetTextColor();

  void SetBackgroundColor(SDL_Color color);
  SDL_Color GetBackgroundColor();

  void SetBorderColor(SDL_Color color);
  SDL_Color GetBorderColor();

  void SetHighlightColor(SDL_Color highlightColor);
  SDL_Color GetHighlightColor();

 private:
  MultiItemsProp prop;

  int textSpacing;

  TextArea(ShapeId sid, MultiItemsProp prop);

  static MultiItemsProp LoadTextAreaProp(Configuration *conf);

  void InternalInit();
};

}  // namespace PaceLib