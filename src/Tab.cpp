#include "Tab.hpp"

#include "Root.hpp"

using namespace PaceLib;

Tab::Tab(ShapeId sid, TabProp inputProp) {
  prop = inputProp;

  color = prop.backgroundColor;

  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  hidden = false;

  name = sid.name;

  wtype = WidgetType::TAB;
}

void Tab::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Tab.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    TabProp prop = LoadTabProp(conf);

    Tab *local = new Tab(sid, prop);
    sid.parent->Add(local);
  }
}

void Tab::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Tab::Begin({root->GetCurrent(), name});
}

void Tab::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Tab::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Tab::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tab::Begin(ShapeId sid, TabProp prop) {
  Tab *local = new Tab(sid, prop);
  sid.parent->Add(local);
}

void Tab::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                           prop.backgroundColor.g, prop.backgroundColor.b,
                           prop.backgroundColor.a);
    SDL_RenderFillRect(Window::GetRenderer(), &rect);

    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r,
                           prop.borderColor.g, prop.borderColor.b,
                           prop.backgroundColor.a);
    SDL_RenderRect(Window::GetRenderer(), &rect);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Tab::Add(Shape *s) { shapes.push_back(s); }

void Tab::Update(SDL_Event *e) {
  for (Shape *s : shapes) {
    if (!s->IsHidden()) s->Update(e);
  }
}

Button *Tab::GetButton(std::string child) {
  return static_cast<Button *>(this->Get(child));
}

ButtonTex *Tab::GetButtonTex(std::string child) {
  return static_cast<ButtonTex *>(this->Get(child));
}

Label *Tab::GetLabel(std::string child) {
  return static_cast<Label *>(this->Get(child));
}

Widget *Tab::GetWidget(std::string child) {
  return static_cast<Widget *>(this->Get(child));
}

TabProp Tab::LoadTabProp(Configuration *conf) {
  float dim[4];
  Root::ParseRect("rect", dim, conf);

  Root *root = &Root::GetInstance();

  SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};
  SDL_FColor backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());
  SDL_FColor borderColor = Widget::ParseVar("border", conf, root->GetVars());

  TabProp prop = {dimr, backgroundColor, borderColor};
  return prop;
}

void Tab::SetRect(SDL_FRect rect) { prop.rect = rect; }

SDL_FRect Tab::GetRect() { return prop.rect; }

void Tab::SetBackgroundColor(SDL_FColor color) { prop.backgroundColor = color; }
SDL_FColor Tab::GetBackgroundColor() { return prop.backgroundColor; }

void Tab::SetBorderColor(SDL_FColor color) { prop.borderColor = color; }
SDL_FColor Tab::GetBorderColor() { return prop.borderColor; }
