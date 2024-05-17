#include "Label.hpp"

#include "Root.hpp"

using namespace PaceLib;

Label::Label(ShapeId sid, LabelProp inputProp) {
  prop = inputProp;

  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  prop.rect = rect;

  hidden = false;

  name = sid.name;

  wtype = WidgetType::LABEL;

  textSize = 0;
}

Label::Label() {}

Label::~Label() {}

// load all info from conf file ( {dim, color}, {font_name, text}, align )
void Label::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Label.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    LabelProp prop = LoadLabelProp(conf);

    Label *newb = new Label(sid, prop);

    sid.parent->Add(newb);

    newb->InternalInit();
  }
}

void Label::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Label::Begin({root->GetCurrent(), name});
}

void Label::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Label::Begin({root->GetCurrent(), name});
  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Label::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Label::Begin(ShapeId sid, LabelProp prop) {
  Label *newb = new Label(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(newb);

  static_cast<Label *>(root->GetCurrent()->Get(sid.name))->InternalInit();
}

void Label::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                           prop.backgroundColor.g, prop.backgroundColor.b,
                           prop.backgroundColor.a);
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

int Label::GetTextSize() { return textSize; }

void Label::SetText(std::string text) {
  if (prop.text == "") {
    delete shapes[0];
    shapes.clear();
    shapesNames.clear();

    prop.text = text;

    InternalInit();
  }

  Text *to = static_cast<Text *>(Get(name + "_text"));

  to->SetText(text);
  prop.text = text;
}

void Label::InternalInit() {
  // child text
  TextProp tprop = {prop.scene,    prop.font, GetRect().x + GetRect().w / 20,
                    GetRect().y,   nullptr,   prop.text,
                    prop.textColor};

  Text::Begin({this, name + "_text"}, tprop);

  Text *to = static_cast<Text *>(Get(name + "_text"));
  to->GetProp()->color = GetProp()->textColor;
  textSize = to->GetWidth();

  SetTextAlign(prop.align);
}

void Label::SetTextAlign(HorizontalAlign align) {
  Text *to = static_cast<Text *>(Get(name + "_text"));

  to->SetY(GetHalfY() - to->GetHeight() / 2);

  if (align.halign == H::MID) {
    to->SetX(GetHalfX() - to->GetWidth() / 2);
  } else if (align.halign == H::RIGHT) {
    to->SetX(GetRect().x + GetRect().w - to->GetWidth() - rect.w / 20);
  } else if (align.halign == H::LEFT) {
    to->SetX(GetRect().x + rect.w / 20);
  }
}

LabelProp Label::LoadLabelProp(Configuration *conf) {
  int dim[4];
  Root::ParseDim(dim, conf);

  HorizontalAlign align;
  if (conf->Get("align") == "left")
    align.halign = H::LEFT;
  else if (conf->Get("align") == "mid")
    align.halign = H::MID;
  else if (conf->Get("align") == "right")
    align.halign = H::RIGHT;

  Root *root = &Root::GetInstance();

  SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
  SDL_Color backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());
  SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
  SDL_Color highlightColor =
      Widget::ParseVar("highlight", conf, root->GetVars());
  std::string text = conf->Get("text").get<std::string>();
  SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());
  std::string font = conf->Get("font").get<std::string>();
  std::string scene = conf->Get("scene").get<std::string>();

  LabelProp prop = {
      scene,           font,        dimr,          text, textColor, align,
      backgroundColor, borderColor, highlightColor};
  return prop;
}
