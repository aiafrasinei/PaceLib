#include "Sprite.hpp"

#include "Root.hpp"
#include "Window.hpp"

using namespace PaceLib;

Sprite::Sprite(ShapeId sid, SpriteProp inputProp) {
  prop = inputProp;

  rect = prop.rect;
  dest_rect = prop.rect;

  if (sid.parent->name != "root") {
    dest_rect.x = sid.parent->GetRect().x + prop.rect.x;
    dest_rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  dest_rect.w = prop.rect.w;
  dest_rect.h = prop.rect.h;

  hidden = false;

  name = sid.name;

  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.w = prop.offset;
  src_rect.h = prop.offset;
}

void Sprite::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Sprite.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    int dim[4];
    Root::ParseRect("rect", dim, conf);

    SDL_Texture *tex = Root::GetInstance()
                           .GetScene(conf->Get("scene").get<std::string>())
                           ->GetTex(conf->Get("tex_name").get<std::string>());

    sid.parent->Add(new Sprite(sid, {tex,
                                     {dim[0], dim[1], dim[2], dim[3]},
                                     conf->Get("offset").get<int>(),
                                     conf->Get("nr").get<int>()}));
  }
}

void Sprite::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Sprite::Begin({root->GetCurrent(), name});
}

void Sprite::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Sprite::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Sprite::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Sprite::Begin(ShapeId sid, SpriteProp prop) {
  sid.parent->Add(new Sprite(sid, prop));
}

void Sprite::Draw() {
  if (!hidden) {
    SDL_RenderCopy(Window::GetRenderer(), prop.tex, &src_rect, &dest_rect);
    src_rect.x = src_rect.x + prop.offset;
    if (src_rect.x == prop.nr * prop.offset) {
      src_rect.x = 0;
    }
  }
}

void Sprite::SetTex(SDL_Texture *tex) { prop.tex = tex; }
SDL_Texture *Sprite::GetTex() { return prop.tex; }

void Sprite::SetOffset(int offset) { prop.offset = offset; }
int Sprite::GetOffset() { return prop.offset; }

void Sprite::SetNr(int nr) { prop.nr = nr; }
int Sprite::GetNr() { return prop.nr; }
