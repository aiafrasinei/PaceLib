#include "Texture.hpp"

#include "Root.hpp"

using namespace PaceLib;

Texture::Texture(ShapeId sid, TexProp inputProp) {
  prop = inputProp;

  rect = prop.rect;

 if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  prop.rect = rect;

  hidden = false;

  name = sid.name;

  wtype = WidgetType::TEXTURE;
}

void Texture::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Texture.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    int dim[4];
    Root::ParseDim(dim, conf);

    SDL_Texture *tex = Root::GetInstance()
                           .GetScene(conf->Get("scene").get<std::string>())
                           ->GetTex(conf->Get("tex_name").get<std::string>());
    sid.parent->Add(new Texture(sid, { tex, {dim[0], dim[1], dim[2], dim[3]} }));
  }
}

void Texture::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Texture::Begin({root->GetCurrent(), name});
}

void Texture::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Texture::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Texture::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Texture::Draw() {
  if (!hidden) {
    SDL_RenderCopy(Window::GetRenderer(), prop.tex, nullptr, &prop.rect);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Texture::Begin(ShapeId sid, TexProp inputProp) {
  sid.parent->Add(new Texture(sid, inputProp));
}
