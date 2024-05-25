#include "Texture.hpp"

#include "Root.hpp"

using namespace PaceLib;

Texture::Texture(ShapeId sid, TextureProp inputProp) {
  prop = inputProp;

  if(prop.dstrect != nullptr) {
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

    float dim[4];
    Root::ParseRect("rect", dim, conf);

    SDL_Texture *tex = Root::GetInstance()
                           .GetScene(conf->Get("scene").get<std::string>())
                           ->GetTex(conf->Get("tex_name").get<std::string>());

    SDL_FRect *srcrectInstance = nullptr;

    nlohmann::json data = conf->Get("srcrect");
    if(data.size() > 0) {
      float srcrect[4];
      Root::ParseRect("srcrect", srcrect, conf);
      SDL_FRect temp = {srcrect[0], srcrect[1], srcrect[2], srcrect[3]};
      srcrectInstance = &temp;
    }

    SDL_FRect *dstrectInstance = nullptr;
  
    data = conf->Get("dstrect");
    if(data.size() > 0) {
      float destrect[4];
      Root::ParseRect("dstrect", destrect, conf);
      SDL_FRect temp = {destrect[0], destrect[1], destrect[2], destrect[3]};
      dstrectInstance = &temp;
    }

    double angle = conf->Get("angle").get<double>();
    
    std::string flipstr = conf->Get("flip").get<std::string>();
    SDL_FlipMode flip;
    if(flipstr == "none") {
      flip = SDL_FlipMode::SDL_FLIP_NONE;
    } else if (flipstr == "vertical") {
      flip = SDL_FlipMode::SDL_FLIP_VERTICAL;
    } else if (flipstr == "horizontal") {
      flip = SDL_FlipMode::SDL_FLIP_HORIZONTAL;
    }

    SDL_FPoint *center = nullptr;
    data = conf->Get("center");
    if(data.size() > 0) {
      float cen[2];
      cen[0] = std::stoi(data[0].get<std::string>());
      cen[1] = std::stoi(data[1].get<std::string>());
      SDL_FPoint temp = {cen[0], cen[1]};
      center = &temp;
    }

    TextureProp nt = { tex,
    srcrectInstance, 
    dstrectInstance,
    angle, center, flip};

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
    SDL_RenderTextureRotated(Window::GetRenderer(), prop.tex, prop.srcrect, prop.dstrect, prop.angle, prop.center, prop.flip);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Texture::Begin(ShapeId sid, TextureProp inputProp) {
  sid.parent->Add(new Texture(sid, inputProp));
}