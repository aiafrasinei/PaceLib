#pragma once

#include "Button.hpp"
#include "Tab.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class Tabber : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "rect" : ["W_3%", "W_30%", "W_19%", "W_19%"],
      "background" : [70, 80, 70, 255],
      "border" : "$BORDER",
      "header_background" : [40, 40, 40, 255],
      "header_height" : 10,
      "buttons_font" : "default",
      "buttons_text_color" : "$TEXT",
      "buttons_text_align" : "left",
      "buttons_background" : "$BACKGROUND",
      "buttons_border" : "$BORDER",
      "buttons_highlight" : "$HIGHLIGHT"
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  static void BeginBlock(std::string name);
  static void EndBlock();

  static void BeginTabBlock(std::string text);
  static void EndTabBlock();

  // programmatic

  static void Begin(ShapeId sid, TabberProp prop);

  // end static methods

  void Draw();

  void AddTab(std::string text);
  void AddTab(std::string name, std::string text);

  Tab *GetTab(std::string child);

  Tab *GetTab(int index);

  int GetNrTabs();

  void SelectTab(int index);

  void SelectTab(std::string name);

  void Update(SDL_Event *e);

  // setters, getters
  void SetScene(std::string scene);
  std::string GetScene();

  void SetFont(std::string font);
  std::string GetFont();

  void SetBackgroundColor(SDL_Color color);
  SDL_Color GetBackgroundColor();

  void SetBorderColor(SDL_Color color);
  SDL_Color GetBorderColor();

  void SetHeaderBackgrounColor(SDL_Color color);
  SDL_Color GetHeaderBackgroundColor();

  void SetHeaderHeight(int headerHeight);
  int GetHeaderHeight();

  void SetButtonsTextColor(SDL_Color color);
  SDL_Color GetButtonsTextColor();

  void SetButtonsTextAlign (HorizontalAlign align);
  HorizontalAlign GetButtonsTextAlign();

  void SetButtonsBackgroundColor(SDL_Color color);
  SDL_Color GetButtonsBackgroundColor();

  void SetButtonsBorderColor(SDL_Color color);
  SDL_Color GetButtonsBorderColor();

  void SetButtonsHighlightColor(SDL_Color color);
  SDL_Color GetButtonsHighlightColor();

  void SetButtonsSelectionColor(SDL_Color color);
  SDL_Color GetButtonsSelectionColor();

  void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

 private:
  std::string scene;

  std::string font;

  std::vector<std::string> titles;

  SDL_Color textColor;

  int bcounter;

  SDL_Rect top;

  static unsigned int current;
  static int tabx;

  TabberProp prop;

  static TabberProp LoadTabberProp(Configuration *conf);

  Tabber(ShapeId sid, TabberProp inputProp);

  void ClearHeaderColor(SDL_Color col);
};

}