#pragma once

#include <SDL3/SDL.h>

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
  GRID,
  BUTTONTEXGRID,
  CUSTOM
};

struct HorizontalAlign {
  H halign;
};

struct PropDimColor {
  SDL_FRect rect;
  SDL_FColor color;
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

struct PointProp {
  float x;
  float y;
  SDL_FColor color;
};

struct VertsProp {
  std::vector<SDL_FPoint> verts;
  SDL_FColor color;
};

struct SpriteProp {
  SDL_Texture *tex;
  SDL_FRect rect;
  int offset;
  int nr;
};

struct LabelProp {
  std::string scene;
  std::string font;
  SDL_FRect rect;
  std::string text;
  SDL_FColor textColor;
  HorizontalAlign align;
  SDL_FColor backgroundColor;
  SDL_FColor borderColor;
  SDL_FColor highlightColor;
};

struct TabberProp {
  std::string scene;
  std::string font;
  SDL_FRect rect;
  SDL_FColor backgroundColor;
  SDL_FColor borderColor;
  SDL_FColor headerBackgroundColor;
  int headerHeight;
  SDL_FColor buttonsTextColor;
  HorizontalAlign buttonsTextAlign;
  SDL_FColor buttonsBackgroundColor;
  SDL_FColor buttonsBorderColor;
  SDL_FColor buttonsHighlightColor;
  SDL_FColor buttonsSelectionColor;
};

struct TabProp {
  SDL_FRect rect;
  SDL_FColor backgroundColor;
  SDL_FColor borderColor;
};

struct TextProp {
  std::string scene;
  std::string font;
  float x, y;
  SDL_Texture *tex;
  std::string text;
  SDL_FColor color;
};

struct TexProp {
  SDL_Texture *tex;
  SDL_FRect rect;
};

struct TextureProp {
  SDL_Texture *tex;
  SDL_FRect *srcrect;
  SDL_FRect *dstrect;
  double angle;
  SDL_FPoint *center;
  SDL_FlipMode flip;
};

struct MultiItemsProp {
  std::string scene;
  std::string font;
  SDL_FRect rect;
  std::vector<std::string> tarr;
  SDL_FColor textColor;
  SDL_FColor backgroundColor;
  SDL_FColor borderColor;
  SDL_FColor highlightColor;
};

struct TooltipProp {
  std::string scene;
  std::string font;
  std::string text;
  SDL_FColor textColor;
  SDL_FColor color;
  SDL_FColor borderColor;
};

struct ButtonTexProp {
  TexProp normal;
  TexProp over;
  SDL_FColor backgroundColor;
  SDL_FColor borderColor;
  SDL_FColor highlightColor;
  bool drawBorder;
};

struct HotspotProp {
  SDL_FRect rect;
  SDL_FColor backgroundColor;
  Hover type;
  SDL_Texture *tex;
};

struct ButtonTexGridProp {
  std::string scene;
  SDL_FRect rect;
  float distance;
  TexProp normal;
  TexProp over;
  SDL_FColor backgroundColor;
  SDL_FColor borderColor;
  SDL_FColor highlightColor;
  bool drawBorder;
};

struct GridProp {
  int x;
  int y;
  int distance;
  int nr;
  SDL_FColor color;
};

}