#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>

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
  SDL_Rect rect;
  SDL_Color color;
};

struct CircleProp {
  int x;
  int y;
  int radius;
  SDL_Color color;
};

struct TriangleProp {
  int x1;
  int y1;
  int x2;
  int y2;
  int x3;
  int y3;
  SDL_Color color;
};

struct LineProp {
  int x1;
  int y1;
  int x2;
  int y2;
  SDL_Color color;
};

struct PointProp {
  int x;
  int y;
  SDL_Color color;
};

struct VertsProp {
  std::vector<SDL_Point> verts;
  SDL_Color color;
};

struct SpriteProp {
  SDL_Texture *tex;
  SDL_Rect dim;
  int offset;
  int nr;
};

struct LabelProp {
  std::string scene;
  std::string font;
  SDL_Rect rect;
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
  SDL_Rect rect;
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
  SDL_Rect rect;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
};

struct TextProp {
  std::string scene;
  std::string font;
  int x, y;
  SDL_Texture *tex;
  std::string text;
  SDL_Color color;
};

struct TexProp {
  SDL_Texture *tex;
  SDL_Rect rect;
};

struct MultiItemsProp {
  std::string scene;
  std::string font;
  SDL_Rect rect;
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
  SDL_Rect rect;
  SDL_Color backgroundColor;
  Hover type;
  SDL_Texture *tex;
};

struct ButtonTexGridProp {
  std::string scene;
  SDL_Rect rect;
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