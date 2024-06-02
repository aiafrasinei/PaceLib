#include "Polygon.hpp"

#include "Root.hpp"

using namespace PaceLib;

Polygon::Polygon(ShapeId sid, std::vector<SDL_Vertex> verts) {
  this->verts = verts;

  for (int i = 0; i < verts.size(); i++) {
    if (sid.parent->name != "root") {
      verts[i].position.x = sid.parent->GetRect().x + verts[i].position.x;
      verts[i].position.y = sid.parent->GetRect().y + verts[i].position.y;
    }
  }

  hidden = false;

  name = sid.name;
}

void Polygon::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Polygon.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    std::vector<float> all_verts = conf->Get("verts").get<std::vector<float>>();
    std::vector<unsigned char> all_colors =
        conf->Get("colors").get<std::vector<unsigned char>>();

    std::vector<SDL_Vertex> verts;

    int vsize = all_verts.size() / 2;
    int index = 0;
    for (int i = 0; i < vsize; i++) {
      SDL_Vertex v;
      v.position.x = all_verts[index];
      v.position.y = all_verts[++index];
      verts.push_back(v);
      index++;
    }

    index = 0;
    for (int i = 0; i < vsize; i++) {
      SDL_Color c{all_colors[index], all_colors[++index], all_colors[++index],
                  all_colors[++index]};
      verts[i].color = c;
      index++;
    }

    sid.parent->Add(new Polygon(sid, verts));
  }
}

void Polygon::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Polygon::Begin({root->GetCurrent(), name});
}

void Polygon::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Polygon::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Polygon::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Polygon::Begin(ShapeId sid, std::vector<SDL_Vertex> verts) {
  sid.parent->Add(new Polygon(sid, verts));
}

void Polygon::Draw() {
  if (!hidden) {
    SDL_RenderGeometry(Window::GetRenderer(), nullptr, &verts[0], verts.size(),
                       nullptr, 0);
  }
}

void Polygon::SetVerts(std::vector<SDL_Vertex> verts) { verts = verts; }
std::vector<SDL_Vertex> Polygon::GetVerts() { return verts; }