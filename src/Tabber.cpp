#include "Tabber.hpp"

#include "Root.hpp"

using namespace PaceLib;

static bool once = true;
static bool just_once = true;
static int nrtabs = 0;
static int nrtitles = 0;

unsigned int Tabber::current = 0;
float Tabber::tabx = 0;

Tabber::Tabber(ShapeId sid, TabberProp inputProp) {
  prop = inputProp;

  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  prop.rect = rect;

  hidden = false;

  name = sid.name;

  current = 0;

  bcounter = 0;

  top = {rect.x, rect.y, rect.w,
         (float)(Window::height * prop.headerHeight / 100)};

  wtype = WidgetType::TABBER;

  nrtabs = 0;

  tabx = Window::height * 1 / 100;
}

void Tabber::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Tabber.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    TabberProp prop = LoadTabberProp(conf);

    sid.parent->Add(new Tabber(sid, prop));
  }
}

void Tabber::Begin(std::string name) {
  Root *root = &Root::GetInstance();

  Tabber::Begin({static_cast<Widget *>(root->GetCurrent()), name});
}

void Tabber::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Tabber::Begin({static_cast<Widget *>(root->GetCurrent()), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Tabber::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tabber::Begin(ShapeId sid, TabberProp prop) {
  sid.parent->Add(new Tabber(sid, prop));
}

void Tabber::SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  textColor.r = r;
  textColor.g = g;
  textColor.b = b;
  textColor.a = a;
}

void Tabber::Draw() {
  if (!hidden) {
    if (just_once) {
      static_cast<Button *>(Get("h_" + std::to_string(current)))
          ->SetBackgroundColor(prop.buttonsSelectionColor);
      just_once = false;
    }
    if (once) {
      for (int i = 0; i < shapesNames.size(); i++) {
        char fc = shapesNames[i][0];
        if (fc == 't') {
          shapes[i]->Hide();
        }
      }
      static_cast<Tab *>(Get("t_" + std::to_string(current)))->Show();
      once = false;
    }

    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                           prop.backgroundColor.g, prop.backgroundColor.b,
                           prop.backgroundColor.a);
    SDL_RenderFillRect(Window::GetRenderer(), &rect);

    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.headerBackgroundColor.r,
                           prop.headerBackgroundColor.g,
                           prop.headerBackgroundColor.b,
                           prop.headerBackgroundColor.a);
    SDL_RenderFillRect(Window::GetRenderer(), &top);

    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r,
                           prop.borderColor.g, prop.borderColor.b,
                           prop.borderColor.a);
    SDL_RenderRect(Window::GetRenderer(), &rect);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Tabber::BeginTabBlock(std::string text) {
  Root *root = &Root::GetInstance();
  Tabber *tabber = static_cast<Tabber *>(root->GetCurrent());

  LabelProp prop = {tabber->GetScene(),
                    tabber->GetFont(),
                    {tabx, (float)(Window::height * 1 / 100), 0,
                    (float)(Window::height * (tabber->prop.headerHeight - 1) / 100)},
                    text,
                    tabber->GetButtonsTextColor(),
                    tabber->GetButtonsTextAlign(),
                    tabber->GetButtonsBackgroundColor(),
                    tabber->GetButtonsBorderColor(),
                    tabber->GetButtonsHighlightColor()};
  Button::Begin({root->GetCurrent(), "h_" + std::to_string(nrtitles)}, prop);

  Button *b = static_cast<Button *>(
      root->GetCurrent()->Get("h_" + std::to_string(nrtitles)));

  float real_width = b->GetTextSize() + b->GetTextSize() / 3;
  b->SetRectW(real_width);
  b->SetTextAlign(prop.align);

  tabx = tabx + real_width + tabber->GetRect().w / 99;

  b->mouseLeftButtonUpCallback = [b, tabber]() {
    std::size_t pos = b->name.find("_");
    int index = std::stoi(b->name.substr(pos + 1));
    current = index;

    tabber->ClearHeaderColor(tabber->prop.buttonsBackgroundColor);
    b->SetBackgroundColor(tabber->prop.buttonsSelectionColor);
    once = true;
  };

  nrtitles++;

  Tab::Begin({tabber, "t_" + std::to_string(nrtabs)},
             {{0, (float)(Window::height * tabber->prop.headerHeight / 100),
               tabber->GetRect().w, tabber->GetRect().h},
              tabber->GetBackgroundColor()});
  tabber->GetTab("t_" + std::to_string(nrtabs))->Hide();
  root->SetCurrent(tabber->GetTab("t_" + std::to_string(nrtabs)));
  root->GetCurrent()->SetParent(tabber);
  nrtabs++;
}

void Tabber::EndTabBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tabber::Update(SDL_Event *e) {
  for (Shape *s : shapes) {
    if (!s->IsHidden()) s->Update(e);
  }
}

TabberProp Tabber::LoadTabberProp(Configuration *conf) {
  float dim[4];
  Root::ParseRect("rect", dim, conf);

  HorizontalAlign align;
  if (conf->Get("buttons_text_align") == "left")
    align.halign = H::LEFT;
  else if (conf->Get("buttons_text_align") == "mid")
    align.halign = H::MID;
  else if (conf->Get("buttons_text_align") == "right")
    align.halign = H::RIGHT;

  Root *root = &Root::GetInstance();

  std::string font = conf->Get("font").get<std::string>();
  SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};
  SDL_FColor backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());
  SDL_FColor borderColor = Widget::ParseVar("border", conf, root->GetVars());
  SDL_FColor headerBackgroundColor =
      Widget::ParseVar("header_background", conf, root->GetVars());
  int headerHeightPercent = conf->Get("header_height").get<int>();
  SDL_FColor buttonsTextColor =
      Widget::ParseVar("buttons_text_color", conf, root->GetVars());
  SDL_FColor buttonsBackgroundColor =
      Widget::ParseVar("buttons_background", conf, root->GetVars());
  SDL_FColor buttonsBorderColor =
      Widget::ParseVar("buttons_border", conf, root->GetVars());
  SDL_FColor buttonsHighlightColor =
      Widget::ParseVar("buttons_highlight", conf, root->GetVars());
  SDL_FColor buttonsSelectionColor =
      Widget::ParseVar("buttons_selection_color", conf, root->GetVars());

  TabberProp prop = {conf->Get("scene").get<std::string>(),
                     font,
                     dimr,
                     backgroundColor,
                     borderColor,
                     headerBackgroundColor,
                     headerHeightPercent,
                     buttonsTextColor,
                     align,
                     buttonsBackgroundColor,
                     buttonsBorderColor,
                     buttonsHighlightColor,
                     buttonsSelectionColor};
  return prop;
}

Tab *Tabber::GetTab(std::string child) {
  return static_cast<Tab *>(Get(child));
}

Tab *Tabber::GetTab(int index) {
  return static_cast<Tab *>(Get("t_" + std::to_string(index)));
}

int Tabber::GetNrTabs() { return shapes.size(); }

void Tabber::SelectTab(int index) {
  current = index;
  once = true;
}

void Tabber::SelectTab(std::string name) {
  int index = 0;
  for (int i = 0; i < shapes.size(); i++) {
    if (static_cast<Button *>(Get("h_" + std::to_string(i)))->GetText() ==
        name) {
      index = i;
      break;
    }
  }

  current = index;
  once = true;
}

void Tabber::ClearHeaderColor(SDL_FColor col) {
  for (int i = 0; i < nrtitles; i++) {
    static_cast<Button *>(Get("h_" + std::to_string(i)))
        ->SetBackgroundColor(col);
  }
}

void Tabber::SetScene(std::string scene) { prop.scene = scene; }
std::string Tabber::GetScene() { return prop.scene; }

void Tabber::SetFont(std::string font) { prop.font = font; }
std::string Tabber::GetFont() { return prop.font; }

void Tabber::SetBackgroundColor(SDL_FColor color) {
  prop.backgroundColor = color;
}
SDL_FColor Tabber::GetBackgroundColor() { return prop.backgroundColor; }

void Tabber::SetBorderColor(SDL_FColor color) { prop.borderColor = color; }
SDL_FColor Tabber::GetBorderColor() { return prop.borderColor; }

void Tabber::SetHeaderBackgrounColor(SDL_FColor color) {
  prop.headerBackgroundColor = color;
}
SDL_FColor Tabber::GetHeaderBackgroundColor() {
  return prop.headerBackgroundColor;
}

void Tabber::SetHeaderHeight(int headerHeight) {
  prop.headerHeight = headerHeight;
}
int Tabber::GetHeaderHeight() { return prop.headerHeight; }

void Tabber::SetButtonsTextColor(SDL_FColor color) {
  prop.buttonsTextColor = color;
}
SDL_FColor Tabber::GetButtonsTextColor() { return prop.buttonsTextColor; }

void Tabber::SetButtonsTextAlign(HorizontalAlign align) {
  prop.buttonsTextAlign = align;
}
HorizontalAlign Tabber::GetButtonsTextAlign() { return prop.buttonsTextAlign; }

void Tabber::SetButtonsBackgroundColor(SDL_FColor color) {
  prop.buttonsBackgroundColor = color;
}
SDL_FColor Tabber::GetButtonsBackgroundColor() {
  return prop.buttonsBackgroundColor;
}

void Tabber::SetButtonsBorderColor(SDL_FColor color) {
  prop.buttonsBorderColor = color;
}
SDL_FColor Tabber::GetButtonsBorderColor() { return prop.buttonsBorderColor; }

void Tabber::SetButtonsHighlightColor(SDL_FColor color) {
  prop.buttonsHighlightColor = color;
}
SDL_FColor Tabber::GetButtonsHighlightColor() {
  return prop.buttonsHighlightColor;
}

void Tabber::SetButtonsSelectionColor(SDL_FColor color) {
  prop.buttonsSelectionColor = color;
}
SDL_FColor Tabber::GetButtonsSelectionColor() {
  return prop.buttonsSelectionColor;
}