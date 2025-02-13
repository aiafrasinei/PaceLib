#include "graphics/points/Point.hpp"

#include "Root.hpp"

using namespace PaceLib;

Point::Point(ShapeId sid, PointProp inputProp) {
  prop = inputProp;
  color = prop.color;

  if (sid.name != "root") {
    prop.x = sid.parent->GetRect().x + prop.x;
    prop.y = sid.parent->GetRect().y + prop.y;
  }

  hidden = false;
}

void Point::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Point.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    float x = conf->Get("x");
    float y = conf->Get("y");

    SDL_FColor color = {conf->Get("color")[0], conf->Get("color")[1],
                        conf->Get("color")[2], conf->Get("color")[3]};
    sid.parent->Add(new Point(sid, {x, y, color}));
  }
}

void Point::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Point::Begin({root->GetCurrent(), name});
}

void Point::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Point::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Point::Begin(ShapeId sid, PointProp prop) {
  sid.parent->Add(new Point(sid, prop));
}

void Point::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Point::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b,
                           color.a);
    SDL_RenderPoint(Window::GetRenderer(), prop.x, prop.y);
  }
}

void Point::SetX(int x) { prop.x = x; }
int Point::GetX() { return prop.x; }

void Point::SetY(int y) { prop.y = y; }
int Point::GetY() { return prop.y; }
