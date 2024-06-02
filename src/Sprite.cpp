#include "Sprite.hpp"

#include "Root.hpp"
#include "Window.hpp"

using namespace PaceLib;

Sprite::Sprite(ShapeId sid, SpriteProp prop) {
  this->prop = prop;

  rect = this->prop.dim;

  dest_rect = this->prop.dim;
  tex = this->prop.tex;

  if (sid.parent->name != "root") {
    dest_rect.x = sid.parent->GetRect().x + prop.dim.x;
    dest_rect.y = sid.parent->GetRect().y + prop.dim.y;
  }

  dest_rect.w = this->prop.dim.w;
  dest_rect.h = this->prop.dim.h;

  hidden = false;

  name = sid.name;

  offset = this->prop.offset;
  nr = this->prop.nr;

  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.w = this->prop.offset;
  src_rect.h = this->prop.offset;
}

Sprite::~Sprite() {}

void Sprite::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Sprite.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    float dim[4];
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
    SDL_RenderTexture(Window::GetRenderer(), tex, &src_rect, &dest_rect);
    src_rect.x = src_rect.x + offset;
    if (src_rect.x == nr * offset) {
      src_rect.x = 0;
    }
  }
}

void Sprite::SetTex(SDL_Texture *tex) { this->tex = tex; }

void Sprite::SetRect(SDL_FRect dim) {
  dest_rect.x = dim.x;
  dest_rect.y = dim.y;
  dest_rect.w = dim.w;
  dest_rect.h = dim.h;
}
