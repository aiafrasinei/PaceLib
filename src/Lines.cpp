#include "graphics/lines/Lines.hpp"
#include "Root.hpp"

using namespace PaceLib;

Lines::Lines(ShapeId sid, VertsProp prop) {
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

Lines::~Lines() {}

void Lines::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Lines.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    std::vector<int> all_verts = conf->Get("verts").get<std::vector<int>>();

    std::vector<SDL_Point> verts;

    int vsize = all_verts.size() / 2;
    int index = 0;
    for (int i = 0; i < vsize; i++) {
      SDL_Point v;
      v.x = all_verts[index];
      v.y = all_verts[++index];
      verts.push_back(v);
      index++;
    }

    SDL_Color color = {conf->Get("color")[0], conf->Get("color")[1],
                       conf->Get("color")[2], conf->Get("color")[3]};

    sid.parent->Add(new Lines(sid, {verts, color}));
  }
}

void Lines::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Lines::Begin({root->GetCurrent(), name});
}

void Lines::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Lines::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Lines::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Lines::Begin(ShapeId sid, VertsProp prop) {
  sid.parent->Add(new Lines(sid, prop));
}

void Lines::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);
    SDL_RenderDrawLines(Window::GetRenderer(), &prop.verts[0], prop.verts.size());
  }
}
