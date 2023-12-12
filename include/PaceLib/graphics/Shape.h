#pragma once

#include "../core/Window.hpp"
#include "../core/interfaces/Drawable.hpp"
#include "../core/interfaces/Hidable.hpp"
#include "../core/interfaces/Updateable.hpp"
#include "../utils/Platform.h"
#include <string>
#include <vector>

namespace PaceLib {

class Shape : public Drawable, public Hidable, public Updateable {
public:
  Shape() {
    hidden = false;
    conf = nullptr;
  }

  virtual ~Shape() {
    for (int i = 0; i < shapes.size(); i++) {
      delete shapes[i];
    }
  }

  void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), r, g, b, a);
    Draw();
  }

  std::string name;
  std::vector<std::string> shapesNames;
  std::vector<Shape *> shapes;

  std::string GetName() { return name; }

  std::vector<Shape *> Get() { return shapes; }

  Shape *Get(int index) { return shapes[index]; }

  Shape *Get(std::string name) {
    for (int i = 0; i < shapesNames.size(); i++) {
      if (shapesNames[i] == name) {
        return shapes[i];
      }
    }

    return nullptr;
  }

  void Add(Shape *s) {
    shapes.push_back(std::move(s));
    shapesNames.push_back(s->name);
  }

  long GetNr() { return shapes.size(); }

  void SetParent(Shape *p) { this->parent = p; }

  Shape *GetParent() { return this->parent; }

  void Update(SDL_Event *e) {}

  void SetRect(float x, float y, float w, float h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
  }

  void SetRect(SDL_Rect rect) { this->rect = rect; }

  void SetRectX(float x) { rect.x = x; }

  void SetRectY(float y) { rect.y = y; }

  void SetRectW(float w) { rect.w = w; }

  void SetRectH(float h) { rect.h = h; }

  SDL_Rect GetRect() { return rect; }

  float GetHalfX() { return rect.x + rect.w / 2; }
  float GetHalfY() { return rect.y + rect.h / 2; }

  Configuration *conf;

protected:
  void LoadDrawColor() {
    Uint8 dr, dg, db, da;

    SDL_GetRenderDrawColor(Window::GetRenderer(), &dr, &dg, &db, &da);
  }

  Shape *current;

  Shape *parent;

  SDL_Rect rect = {0, 0, 0, 0};

private:
};

} // namespace PaceLib
