#include "graphics/points/Points.hpp"

#include "Root.hpp"

using namespace PaceLib;

Points::Points(ShapeId sid, VertsProp prop) {
  this->prop = prop;

  for (int i = 0; i < prop.verts.size(); i++) {
    if (sid.parent->name != "root") {
      prop.verts[i].x = sid.parent->GetRect().x + prop.verts[i].x;
      prop.verts[i].y = sid.parent->GetRect().y + prop.verts[i].y;
    }
  }

  hidden = false;

  name = sid.name;
}

Points::~Points() {}

void Points::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Points.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    std::vector<int> all_verts = conf->Get("verts").get<std::vector<int>>();

    std::vector<SDL_FPoint> verts;

    int vsize = all_verts.size() / 2;
    int index = 0;
    for (int i = 0; i < vsize; i++) {
      SDL_FPoint v;
      v.x = all_verts[index];
      v.y = all_verts[++index];
      verts.push_back(v);
      index++;
    }

    SDL_Color color = {conf->Get("color")[0], conf->Get("color")[1],
                       conf->Get("color")[2], conf->Get("color")[3]};

    sid.parent->Add(new Points(sid, {verts, color}));
  }
}

void Points::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Points::Begin({root->GetCurrent(), name});
}

void Points::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Points::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Points::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Points::Begin(ShapeId sid, VertsProp prop) {
  sid.parent->Add(new Points(sid, prop));
}

void Points::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);
    SDL_RenderPoints(Window::GetRenderer(), &prop.verts[0], prop.verts.size());
  }
}
