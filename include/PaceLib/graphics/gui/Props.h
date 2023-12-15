#pragma once

#include "../utils/SDL2/SDL_FontCache.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

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
  CUSTOM
};

struct HorizontalAlign {
  H halign;
};

struct PropDimColor {
  SDL_Rect rect;
  SDL_Color color;
};

struct PropFontText {
  FC_Font *font;
  std::string text;
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

struct SpriteProp {
  SDL_Texture *tex;
  SDL_Rect dim;
  int offset;
  int nr;
};

struct LabelProp {
  SDL_Rect rect;
  FC_Font *font;
  std::string text;
  SDL_Color textColor;
  HorizontalAlign align;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color highlightColor;
};

struct TabberProp {
  SDL_Rect rect;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color headerBackgroundColor;
  int headerHeight;
  FC_Font *buttonsFont;
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
  int x, y;
  FC_Font *font;
  std::string text;
  SDL_Color color;
};

struct TexProp {
  SDL_Texture *tex;
  SDL_Rect rect;
};

struct MultiItemsProp {
  SDL_Rect rect;
  FC_Font *font;
  std::vector<std::string> tarr;
  SDL_Color textColor;
  SDL_Color backgroundColor;
  SDL_Color borderColor;
  SDL_Color highlightColor;
};

struct TooltipProp {
  FC_Font *font;
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
} // namespace PaceLib