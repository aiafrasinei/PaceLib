#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>

namespace PaceLib {

enum class H { LEFT, MID, RIGHT };

enum class Hover { RECT, FILLED, TEXTURE };

enum class WidgetType {
  ROOT,
  TAB,
  TABBER,
  LABEL,
  BUTTON,
  BUTTONTEX,
  HOTSPOT,
  TOOLTIP,
  TEXTINPUT,
  TEXTAREA,
  CHECKBOX,
  TEXTURE,
  TEXT,
  COMBOBOX,
  GRID,
  BUTTONGRID,
  CUSTOM
};

struct HorizontalAlign {
  H halign;
};

struct PropDimColor {
  SDL_FRect rect;
  SDL_Color color;
};

struct CircleProp {
  float x;
  float y;
  float radius;
  SDL_FColor color;
};

struct TriangleProp {
  float x1;
  float y1;
  float x2;
  float y2;
  float x3;
  float y3;
  SDL_FColor color;
};

struct LineProp {
  float x1;
  float y1;
  float x2;
  float y2;
  SDL_FColor color;
};

struct SpriteProp {
  SDL_Texture *tex;
  SDL_FRect dim;
  int offset;
  int nr;
};

struct LabelProp {
  std::string scene;
  std::string font;
  SDL_FRect rect;
  std::string text;
  SDL_Color textColor;
  HorizontalAlign align;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color highlightColor;
};

struct TabberProp {
  std::string scene;
  std::string font;
  SDL_FRect rect;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color headerBackgroundColor;
  int headerHeight;
  SDL_Color buttonsTextColor;
  HorizontalAlign buttonsTextAlign;
  SDL_Color buttonsBackgroundColor;
  SDL_Color buttonsBorderColor;
  SDL_Color buttonsHighlightColor;
  SDL_Color buttonsSelectionColor;
};

struct TabProp {
  SDL_FRect rect;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
};

struct TextProp {
  std::string scene;
  std::string font;
  float x, y;
  SDL_Texture *tex;
  std::string text;
  SDL_Color color;
};

struct TexProp {
  SDL_Texture *tex;
  SDL_FRect rect;
};

struct MultiItemsProp {
  std::string scene;
  std::string font;
  SDL_FRect rect;
  std::vector<std::string> tarr;
  SDL_Color textColor;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color highlightColor;
};

struct TooltipProp {
  std::string scene;
  std::string font;
  std::string text;
  SDL_Color textColor;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
};

struct ButtonTexProp {
  TexProp normal;
  TexProp over;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color highlightColor;
  bool drawBorder;
};

struct HotspotProp {
  SDL_FRect rect;
  SDL_Color backgroundColor;
  Hover type;
  SDL_Texture *tex;
};

struct ButtonTexGridProp {
  std::string scene;
  SDL_FRect rect;
  float distance;
  TexProp normal;
  TexProp over;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color highlightColor;
  bool drawBorder;
};

struct GridProp {
  float x;
  float y;
  float distance;
  int nr;
  SDL_Color color;
};

} // namespace PaceLib