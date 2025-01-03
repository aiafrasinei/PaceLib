#include "Tooltip.hpp"

#include "Root.hpp"

using namespace PaceLib;

Tooltip::Tooltip(ShapeId sid, TooltipProp inputProp) {
  prop = inputProp;

  color = prop.color;

  parent = sid.parent;

  SDL_FRect child = sid.parent->GetRect();

  child.x = child.x + sid.parent->GetRect().w / 2;
  child.y = child.y + sid.parent->GetRect().h / 2;

  rect = child;

  hidden = false;

  name = sid.name;

  wtype = WidgetType::TOOLTIP;

  textSize = 0;
}

void Tooltip::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_ToolTip.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    Tooltip *dt;

    TooltipProp prop = LoadTooltipProp(conf);

    dt = new Tooltip(sid, prop);
    sid.parent->Add(dt);

    dt->InternalInit();
  }
}

void Tooltip::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Tooltip::Begin({root->GetCurrent(), name});
}

void Tooltip::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Tooltip::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Tooltip::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tooltip::Begin(ShapeId sid, TooltipProp prop) {
  Tooltip *dt = new Tooltip(sid, prop);
  sid.parent->Add(dt);

  dt->InternalInit();
}

void Tooltip::Draw() {
  if (!hidden) {
    float x, y;
    SDL_GetMouseState(&x, &y);

    if (PointInRect({x, y}, static_cast<Widget *>(parent)->GetRect())) {
      SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b,
                             color.a);
      SDL_RenderFillRect(Window::GetRenderer(), &rect);

      SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r,
                             prop.borderColor.g, prop.borderColor.b,
                             prop.borderColor.a);
      SDL_RenderRect(Window::GetRenderer(), &rect);

      for (Shape *w : shapes) {
        w->Draw();
      }
    }
  }
}

void Tooltip::InternalInit() {
  // child text
  Root *root = &Root::GetInstance();
  Tooltip *dt = static_cast<Tooltip *>(root->GetCurrent()->Get(name));

  TextProp tprop = {
      prop.scene,      prop.font, dt->GetRect().x + dt->GetRect().w / 20,
      dt->GetRect().y, nullptr,   prop.text,
      prop.textColor};

  Text::Begin({dt, dt->name + "_text"}, tprop);

  Text *to = static_cast<Text *>(dt->Get(name + "_text"));

  to->SetX(dt->GetRect().x);
  to->SetY(dt->GetRect().y);

  textSize = to->GetWidth();
  rect.w = textSize;
}

TooltipProp Tooltip::LoadTooltipProp(Configuration *conf) {
  Root *root = &Root::GetInstance();

  SDL_FColor backgroundColor = Widget::ParseVar("color", conf, root->GetVars());
  SDL_FColor borderColor = Widget::ParseVar("border", conf, root->GetVars());
  std::string text = conf->Get("text").get<std::string>();
  SDL_FColor textColor = Widget::ParseVar("text_color", conf, root->GetVars());
  std::string font = conf->Get("font").get<std::string>();

  TooltipProp prop = {conf->Get("scene").get<std::string>(),
                      font,
                      text,
                      textColor,
                      backgroundColor,
                      borderColor};
  return prop;
}

void Tooltip::SetText(std::string text) { prop.text = text; }
std::string Tooltip::GeText() { return prop.text; }

void Tooltip::SetTextColor(SDL_FColor color) { prop.textColor = color; }
SDL_FColor Tooltip::GetTextColor() { return prop.textColor; }

void Tooltip::SetBorderColor(SDL_FColor color) { prop.borderColor = color; }
SDL_FColor Tooltip::GetBorderColor() { return prop.borderColor; }
