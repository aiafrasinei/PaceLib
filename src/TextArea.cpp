#include "TextArea.hpp"

#include "Root.hpp"

using namespace PaceLib;

TextArea::TextArea(ShapeId sid, MultiItemsProp prop) {
  this->prop = prop;
  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  this->prop.rect = rect;

  hidden = false;

  textSpacing = 20;

  this->name = sid.name;

  wtype = WidgetType::TEXTAREA;
}

TextArea::~TextArea() {}

void TextArea::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_TextArea.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    MultiItemsProp prop = LoadTextAreaProp(conf);

    TextArea *ta = new TextArea(sid, prop);
    sid.parent->Add(ta);

    ta->InternalInit();
  }
}

void TextArea::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  TextArea::Begin({root->GetCurrent(), name});
}

void TextArea::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  TextArea::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void TextArea::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void TextArea::Begin(ShapeId sid, MultiItemsProp prop) {
  TextArea *ta = new TextArea(sid, prop);
  sid.parent->Add(ta);

  Root *root = &Root::GetInstance();
  static_cast<TextArea *>(root->GetCurrent()->Get(sid.name))->InternalInit();
}

void TextArea::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                           prop.backgroundColor.g, prop.backgroundColor.b,
                           prop.backgroundColor.a);
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

void TextArea::SetTextSpacing(int size) { this->textSpacing = size; }

void TextArea::InternalInit() {
  Root *root = &Root::GetInstance();
  TextArea *ta = static_cast<TextArea *>(root->GetCurrent()->Get(name));

  float ry = rect.y;
  int i = 0;
  for (std::string text : prop.tarr) {
    TextProp tprop = {prop.scene, prop.font, rect.x + rect.w / 50, ry,
                      nullptr,    text,      prop.textColor};

    Text::Begin({ta, ta->name + "_text" + std::to_string(i)}, tprop);

    Text *to = static_cast<Text *>(ta->Get(name + "_text" + std::to_string(i)));
    to->SetX(GetRect().x + rect.w / 20);
    to->SetY(ry);

    ry = ry + 20;
    i++;
  }
}

MultiItemsProp TextArea::LoadTextAreaProp(Configuration *conf) {
  float dim[4];
  Root::ParseDim(dim, conf);

  Root *root = &Root::GetInstance();

  SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};
  SDL_Color backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());
  SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
  SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());
  std::vector<std::string> tarr =
      conf->Get("text_arr").get<std::vector<std::string>>();
  std::string font = conf->Get("font").get<std::string>();

  MultiItemsProp prop = {conf->Get("scene").get<std::string>(),
                         font,
                         dimr,
                         tarr,
                         textColor,
                         backgroundColor,
                         borderColor};
  return prop;
}
