#include "Texture.hpp"

#include "Root.hpp"

using namespace PaceLib;

Texture::Texture(ShapeId sid, TextureProp inputProp) {
  prop = inputProp;

  if (prop.dstrect != nullptr) {
    rect.x = (*prop.dstrect).x;
    rect.y = (*prop.dstrect).y;
    rect.w = (*prop.dstrect).w;
    rect.h = (*prop.dstrect).h;
  }

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + (*prop.dstrect).x;
    rect.y = sid.parent->GetRect().y + (*prop.dstrect).y;
  }

  prop.dstrect = &rect;

  hidden = false;

  name = sid.name;

  wtype = WidgetType::TEXTURE;
}

void Texture::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Texture.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    SDL_Texture *tex = Root::GetInstance()
                           .GetScene(conf->Get("scene").get<std::string>())
                           ->GetTex(conf->Get("tex_name").get<std::string>());

    SDL_Rect *srcrectInstance = nullptr;

    nlohmann::json data = conf->Get("srcrect");
    if (data.size() > 0) {
      int srcrect[4];
      Root::ParseRect("srcrect", srcrect, conf);
      SDL_Rect temp = {srcrect[0], srcrect[1], srcrect[2], srcrect[3]};
      srcrectInstance = &temp;
    }

    SDL_Rect *dstrectInstance = nullptr;

    data = conf->Get("dstrect");
    if (data.size() > 0) {
      int destrect[4];
      Root::ParseRect("dstrect", destrect, conf);
      SDL_Rect temp = {destrect[0], destrect[1], destrect[2], destrect[3]};
      dstrectInstance = &temp;
    }

    double angle = conf->Get("angle").get<double>();

    std::string flipstr = conf->Get("flip").get<std::string>();
    SDL_RendererFlip flip;
    if (flipstr == "none") {
      flip = SDL_RendererFlip::SDL_FLIP_NONE;
    } else if (flipstr == "vertical") {
      flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
    } else if (flipstr == "horizontal") {
      flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
    }

    SDL_Point *center = nullptr;
    data = conf->Get("center");
    if (data.size() > 0) {
      int cen[2];
      cen[0] = std::stoi(data[0].get<std::string>());
      cen[1] = std::stoi(data[1].get<std::string>());
      SDL_Point temp = {cen[0], cen[1]};
      center = &temp;
    }

    TextureProp nt = {tex,   srcrectInstance, dstrectInstance,
                      angle, center,          flip};

    sid.parent->Add(new Texture(sid, nt));
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
    SDL_RenderCopyEx(Window::GetRenderer(), prop.tex, prop.srcrect,
                     prop.dstrect, prop.angle, prop.center, prop.flip);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Texture::Begin(ShapeId sid, TextureProp inputProp) {
  sid.parent->Add(new Texture(sid, inputProp));
}

void Texture::SetTex(SDL_Texture *tex) { prop.tex = tex; }
SDL_Texture *Texture::GetTex() { return prop.tex; }

void Texture::SetSrcRect(SDL_Rect *srcrect) { prop.srcrect = srcrect; }
SDL_Rect *Texture::GetSrcRect() { return prop.srcrect; }

void Texture::SetDstRect(SDL_Rect *dstrect) { prop.dstrect = dstrect; }
SDL_Rect *Texture::GetDstRect() { return prop.dstrect; }

void Texture::SetAngle(double angle) { prop.angle = angle; }
double Texture::GetAngle() { return prop.angle; }

void Texture::SetCenter(SDL_Point *center) { prop.center = center; }
SDL_Point *Texture::GetCenter() { return prop.center; }

void Texture::SetFlip(SDL_RendererFlip flip) { prop.flip = flip; }
SDL_RendererFlip Texture::GetFlip() { return prop.flip; }
