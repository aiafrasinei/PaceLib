#include "graphics/lines/Line.hpp"
#include "Root.hpp"

using namespace PaceLib;

Line::Line(ShapeId sid, LineProp prop) {
  this->prop = prop;

  if (sid.name != "root") {
    this->prop.x1 = sid.parent->GetRect().x + prop.x1;
    this->prop.y1 = sid.parent->GetRect().y + prop.y1;
    this->prop.x2 = sid.parent->GetRect().x + prop.x2;
    this->prop.y2 = sid.parent->GetRect().y + prop.y2;
  }

  hidden = false;
}

Line::~Line() {}

void Line::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Line.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    int x1 = conf->Get("x1");
    int y1 = conf->Get("y1");
    int x2 = conf->Get("x2");
    int y2 = conf->Get("y2");

    SDL_Color color = {conf->Get("color")[0], conf->Get("color")[1],
                       conf->Get("color")[2], conf->Get("color")[3]};
    sid.parent->Add(new Line(sid, {x1, y1, x2, y2, color}));
  }
}

void Line::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Line::Begin({root->GetCurrent(), name});
}

void Line::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Line::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Line::Begin(ShapeId sid, LineProp prop) {
  sid.parent->Add(new Line(sid, prop));
}

void Line::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Line::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);
    SDL_RenderDrawLine(Window::GetRenderer(), prop.x1, prop.y1, prop.x2,
                       prop.y2);
  }
}
