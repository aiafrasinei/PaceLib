#include "Button.h"
#include "ConLog.hpp"
#include "Root.h"
#include <functional>

using namespace PaceLib;

Button::Button(ShapeId sid, LabelProp prop) : Label(sid, prop) {
  highlight = true;

  wtype = WidgetType::BUTTON;

  onClickCallback = nullptr;
}

Button::~Button() {}

// load all info from conf file ( {dim, color}, {font_name, text}, align )
void Button::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Button.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    LabelProp prop = LoadLabelProp(conf);

    Button *newb = new Button(sid, prop);

    sid.parent->Add(newb);

    newb->InternalInit();
  }
}

void Button::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Button::Begin({root->GetCurrent(), name});
}

void Button::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Button::Begin({root->GetCurrent(), name});
  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Button::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Button::Begin(ShapeId sid, LabelProp prop) {
  Button *newb = new Button(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(newb);

  ((Button *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

void Button::Draw() {
  if (!hidden) {
    if (mouseOver) {
      SDL_SetRenderDrawColor(Window::GetRenderer(), prop.highlightColor.r,
                             prop.highlightColor.g, prop.highlightColor.b,
                             prop.highlightColor.a);
    } else {
      SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                             prop.backgroundColor.g, prop.backgroundColor.b,
                             prop.backgroundColor.a);
    }

    SDL_RenderFillRect(Window::GetRenderer(), &rect);

    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r,
                           prop.borderColor.g, prop.borderColor.b,
                           prop.borderColor.a);
    SDL_RenderDrawRect(Window::GetRenderer(), &rect);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Button::Update(SDL_Event *e) {
  if (!hidden) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    static int nr = 0;
    if (e->type == SDL_MOUSEBUTTONUP) {

      if (PointInRect({x, y}, rect)) {
        if (onClickCallback != nullptr) {
          onClickCallback();
          SDL_PollEvent(e);
        }
      }
    }

    if (highlight) {
      if (PointInRect({x, y}, rect)) {
        mouseOver = true;
      } else {
        mouseOver = false;
      }
    }
  }
}

void Button::SetHighlight(bool state) { highlight = state; }
