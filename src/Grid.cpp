#include "Grid.hpp"

#include "Root.hpp"

using namespace PaceLib;

Grid::Grid(ShapeId sid, GridProp inputProp) {
  prop = inputProp;

  rect.x = prop.x;
  rect.y = prop.y;

  color = prop.color;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.x;
    rect.y = sid.parent->GetRect().y + prop.y;
  }

  hidden = false;

  name = sid.name;

  wtype = WidgetType::GRID;
}

void Grid::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Grid.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    GridProp prop = LoadGridProp(conf);

    Grid *newg = new Grid(sid, prop);

    sid.parent->Add(newg);
  }
}

void Grid::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Grid::Begin({root->GetCurrent(), name});
}

void Grid::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Grid::Begin({root->GetCurrent(), name});
  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Grid::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Grid::Begin(ShapeId sid, GridProp prop) {
  Grid *newb = new Grid(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(newb);
}

void Grid::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b,
                           color.a);

    for (int i = 0; i <= prop.nr; i++) {
      for (int j = 0; j <= prop.nr; j++) {
        SDL_RenderDrawLine(
            Window::GetRenderer(), prop.x, prop.y + (i * prop.distance),
            prop.x + prop.distance * prop.nr, prop.y + (i * prop.distance));
        SDL_RenderDrawLine(Window::GetRenderer(), prop.x + (j * prop.distance),
                           prop.y, prop.x + (j * prop.distance),
                           prop.y + prop.distance * prop.nr);
      }
    }

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

GridProp Grid::LoadGridProp(Configuration *conf) {
  Root *root = &Root::GetInstance();

  int x = conf->Get("x").get<int>();
  int y = conf->Get("y").get<int>();
  int distance = conf->Get("distance").get<int>();
  int nr = conf->Get("nr").get<int>();
  SDL_Color color = Widget::ParseVar("color", conf, root->GetVars());

  GridProp prop = {x, y, distance, nr, color};
  return prop;
}

void Grid::SetX(int x) { prop.x = x; }
int Grid::GetX() { return prop.x; }

void Grid::SetY(int y) { prop.y = y; }
int Grid::GetY() { return prop.y; }

void Grid::SetDistance(int distance) { prop.distance = distance; }
int Grid::GetDistance() { return prop.distance; }

void Grid::SetNr(int nr) { prop.nr = nr; }
int Grid::GetNr() { return prop.nr; }

void Grid::SetColor(SDL_Color color) { prop.color = color; }
SDL_Color Grid::GetColor() { return prop.color; }