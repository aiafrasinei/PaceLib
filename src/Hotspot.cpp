#include "Hotspot.hpp"

#include "Root.hpp"

using namespace PaceLib;

Hotspot::Hotspot(ShapeId sid, HotspotProp inputProp) {
  prop = inputProp;

  if (sid.parent->name != "root") {
    prop.rect.x = sid.parent->GetRect().x + prop.rect.x;
    prop.rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  hidden = false;

  name = sid.name;

  mouseOver = false;

  isHighlight = true;

  highlightColor = prop.backgroundColor;

  wtype = WidgetType::HOTSPOT;
}

void Hotspot::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Hotspot.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    float dim[4];
    Root::ParseRect("rect", dim, conf);

    HotspotProp prop = LoadHotspotProp(conf);

    sid.parent->Add(new Hotspot(sid, prop));
  }
}

void Hotspot::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Hotspot::Begin({root->GetCurrent(), name});
}

void Hotspot::Begin(ShapeId sid, HotspotProp prop) {
  sid.parent->Add(new Hotspot(sid, prop));
}

void Hotspot::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Hotspot::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Hotspot::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Hotspot::Draw() {
  if (!hidden) {
    if (mouseOver) {
      SDL_SetRenderDrawColor(Window::GetRenderer(), highlightColor.r,
                             highlightColor.g, highlightColor.b,
                             highlightColor.a);
      if (prop.type == Hover::FILLED) {
        SDL_RenderFillRect(Window::GetRenderer(), &prop.rect);
      } else if (prop.type == Hover::RECT) {
        SDL_RenderRect(Window::GetRenderer(), &prop.rect);
      } else if (prop.type == Hover::TEXTURE) {
        if (tex != nullptr) {
          SDL_RenderTexture(Window::GetRenderer(), prop.tex, nullptr,
                            &prop.rect);
        }
      }
    }

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void Hotspot::Update(SDL_Event *e) {
  if (!hidden) {
    float x, y;
    SDL_GetMouseState(&x, &y);

    UpdateMouse(e, x, y);

    if (isHighlight) {
      if (PointInRect({x, y}, prop.rect)) {
        mouseOver = true;
      } else {
        mouseOver = false;
      }
    }
  }
}

void Hotspot::SetHighlight(bool state) { isHighlight = state; }

void Hotspot::SetHighlightColor(SDL_FColor color) { highlightColor = color; }

HotspotProp Hotspot::LoadHotspotProp(Configuration *conf) {
  float dim[4];
  Root::ParseRect("rect", dim, conf);

  Root *root = &Root::GetInstance();

  SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};
  SDL_FColor backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());

  Hover type;
  std::string stype = conf->Get("type").get<std::string>();
  if (stype == "rect") {
    type = Hover::RECT;
  } else if (stype == "filled") {
    type = Hover::FILLED;
  } else if (stype == "texture") {
    type = Hover::TEXTURE;
  } else {
    type = Hover::RECT;
  }

  SDL_Texture *tex = nullptr;
  if (conf->Get("texture").get<std::string>() != "") {
    tex = root->GetScene(conf->Get("scene"))
              ->GetTex(conf->Get("texture").get<std::string>());
  }

  HotspotProp prop = {dimr, backgroundColor, type, tex};
  return prop;
}

void Hotspot::SetBackgroundColor(SDL_FColor backgroundColor) {
  prop.backgroundColor = backgroundColor;
}
SDL_FColor Hotspot::GetBackgroundColor() { return prop.backgroundColor; }

void Hotspot::SetHover(Hover type) { prop.type = type; }
Hover Hotspot::GetHover() { return prop.type; }

void Hotspot::SetTex(SDL_Texture *tex) { prop.tex = tex; }
SDL_Texture *Hotspot::GetTex() { return prop.tex; }