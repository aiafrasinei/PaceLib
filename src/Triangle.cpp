#include "Triangle.hpp"

#include "Root.hpp"

using namespace PaceLib;

Triangle::Triangle(ShapeId sid, TriangleProp inputProp) {
  prop = inputProp;
  color = prop.color;

  if (sid.parent->name == "root") {
    points[0] = {static_cast<int>(prop.x1), static_cast<int>(prop.y1)};
    points[1] = {static_cast<int>(prop.x2), static_cast<int>(prop.y2)};
    points[2] = {static_cast<int>(prop.x3), static_cast<int>(prop.y3)};
    points[3] = {static_cast<int>(prop.x1), static_cast<int>(prop.y1)};
  } else {
    points[0] = {static_cast<int>(sid.parent->GetRect().x + prop.x1),
                 static_cast<int>(sid.parent->GetRect().y + prop.y1)};
    points[1] = {static_cast<int>(sid.parent->GetRect().x + prop.x2),
                 static_cast<int>(sid.parent->GetRect().y + prop.y2)};
    points[2] = {static_cast<int>(sid.parent->GetRect().x + prop.x3),
                 static_cast<int>(sid.parent->GetRect().y + prop.y3)};
    points[3] = {static_cast<int>(sid.parent->GetRect().x + prop.x1),
                 static_cast<int>(sid.parent->GetRect().y + prop.y1)};
  }

  verts[0].position.x = points[0].x;
  verts[0].position.y = points[0].y;
  verts[0].color = {color.r, color.g, color.b, color.a};

  verts[1].position.x = points[1].x;
  verts[1].position.y = points[1].y;
  verts[1].color = {color.r, color.g, color.b, color.a};

  verts[2].position.x = points[2].x;
  verts[2].position.y = points[2].y;
  verts[2].color = {color.r, color.g, color.b, color.a};

  hidden = false;

  this->name = sid.name;
}

void Triangle::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Triangle.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    int x1 = conf->Get("x1");
    int y1 = conf->Get("y1");
    int x2 = conf->Get("x2");
    int y2 = conf->Get("y2");
    int x3 = conf->Get("x3");
    int y3 = conf->Get("y3");
    SDL_Color color = {conf->Get("color")[0], conf->Get("color")[1],
                       conf->Get("color")[2], conf->Get("color")[3]};

    sid.parent->Add(new Triangle(sid, {x1, y1, x2, y2, x3, y3, color}));
  }
}

void Triangle::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Triangle::Begin({root->GetCurrent(), name});
}

void Triangle::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Triangle::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Triangle::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Triangle::Begin(ShapeId sid, TriangleProp prop) {
  sid.parent->Add(new Triangle(sid, prop));
}

void Triangle::Draw() {
  if (!hidden) {
    SDL_RenderGeometry(Window::GetRenderer(), nullptr, verts, 3, nullptr, 0);
  }
}

void Triangle::SetX1(int x1) { prop.x1 = x1; }
int Triangle::GetX1() { return prop.x1; }

void Triangle::SetY1(int y1) { prop.y1 = y1; }
int Triangle::GetY1() { return prop.y1; }

void Triangle::SetX2(int x2) { prop.x2 = x2; }
int Triangle::GetX2() { return prop.x2; }

void Triangle::SetY2(int y2) { prop.y2 = y2; }
int Triangle::GetY2() { return prop.y2; }

void Triangle::SetX3(int x3) { prop.x3 = x3; }
int Triangle::GetX3() { return prop.x3; }

void Triangle::SetY3(int y3) { prop.y3 = y3; }
int Triangle::GetY3() { return prop.y3; }
