#include "Text.h"
#include "Root.h"
#include "Window.hpp"

using namespace PaceLib;

Text::Text(ShapeId sid, TextProp inputProp) {
  prop = inputProp;

  if (sid.parent->name != "root") {
    prop.x = sid.parent->GetRect().x + prop.x;
    prop.y = sid.parent->GetRect().y + prop.y;
  }

  hidden = false;

  name = sid.name;

  wtype = WidgetType::TEXT;

  Root *root = &Root::GetInstance();
  root->GetScene(prop.scene)->AddFont(name, prop.font, prop.text, prop.color);

  SDL_Texture *tex = root->GetScene(prop.scene)->GetFont(name);
  prop.tex = tex;

  int w, h;
  SDL_QueryTexture(prop.tex, nullptr, nullptr, &w, &h);
  rect = {prop.x, prop.y, w, h};

  SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);
  SDL_RenderCopy(Window::GetRenderer(), prop.tex, NULL, &rect);
}

Text::~Text() {}

void Text::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Text.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    TextProp prop = LoadTextProp(conf);

    Text *t = new Text(sid, prop);

    t->conf = conf;
    sid.parent->Add(t);
  }
}

void Text::Begin(std::string name) {
  Text::Begin({Root::GetInstance().GetCurrent(), name});
}

void Text::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Text::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Text::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Text::Begin(ShapeId sid, TextProp prop) {
  Text *t = new Text(sid, prop);

  sid.parent->Add(t);
}

void Text::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);
    SDL_RenderCopy(Window::GetRenderer(), prop.tex, NULL, &rect);
  }
}

int Text::GetWidth() { return rect.w; }

int Text::GetHeight() { return rect.h; }

void Text::SetX(int x) { prop.x = x; }

void Text::SetY(int y) { prop.y = y; }

std::string Text::GetText() { return prop.text; }

void Text::SetText(std::string text) { prop.text = text; }

TextProp Text::LoadTextProp(Configuration *conf) {
  int pos[2];
  Widget::ParsePos(pos, conf);

  Root *root = &Root::GetInstance();

  std::string font = conf->Get("font").get<std::string>();
  std::string text = conf->Get("text").get<std::string>();
  SDL_Color color = Widget::ParseVar("color", conf, root->GetVars());

  root->GetScene(conf->Get("scene").get<std::string>())->AddFont(root->GetCurrent()->name, font, text, color);

  SDL_Texture *tex = root->GetScene(conf->Get("scene").get<std::string>())
                      ->GetFont(root->GetCurrent()->name);

  TextProp prop = {conf->Get("scene").get<std::string>(), font, pos[0], pos[1], tex, text, color};

  return prop;
}
