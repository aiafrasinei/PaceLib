#include "Rectangle.hpp"

#include "Root.hpp"
#include "Window.hpp"

using namespace PaceLib;

Rectangle::Rectangle(ShapeId sid, PropDimColor prop) {
  this->prop = prop;
  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  hidden = false;

  this->name = sid.name;
}

Rectangle::~Rectangle() {}

void Rectangle::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Rectangle.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    int dim[4];
    Root::ParseRect("dim", dim, conf);

    SDL_Color color = {conf->Get("color")[0], conf->Get("color")[1],
                       conf->Get("color")[2], conf->Get("color")[3]};

    sid.parent->Add(
        new Rectangle(sid, {{dim[0], dim[1], dim[2], dim[3]}, color}));
  }
}

void Rectangle::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Rectangle::Begin({root->GetCurrent(), name});
}

void Rectangle::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Rectangle::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Rectangle::Begin(ShapeId sid, PropDimColor prop) {
  sid.parent->Add(new Rectangle(sid, prop));
}

void Rectangle::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Rectangle::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);

    SDL_RenderFillRect(Window::GetRenderer(), &rect);
  }
}
