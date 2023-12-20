#include "Hotspot.h"
#include "Root.h"

using namespace PaceLib;

Hotspot::Hotspot(ShapeId sid, HotspotProp prop) {
  this->prop = prop;

  if (sid.parent->name != "root") {
    this->prop.rect.x = sid.parent->GetRect().x + prop.rect.x;
    this->prop.rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  hidden = false;

  this->name = sid.name;

  mouseOver = false;

  isHighlight = true;

  this->highlightColor = prop.backgroundColor;

  this->tex = prop.tex;

  wtype = WidgetType::HOTSPOT;

}

Hotspot::~Hotspot() {}

void Hotspot::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Hotspot.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    int dim[4];
    Root::ParseDim(dim, conf);

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
        SDL_RenderDrawRect(Window::GetRenderer(), &prop.rect);
      } else if (prop.type == Hover::TEXTURE) {
        if (tex != nullptr) {
          SDL_RenderCopy(Window::GetRenderer(), tex, nullptr, &prop.rect);
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
    int x, y;
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

void Hotspot::SetHighlightColor(SDL_Color color) { highlightColor = color; }

HotspotProp Hotspot::LoadHotspotProp(Configuration *conf) {
  int dim[4];
  Root::ParseDim(dim, conf);

  Root *root = &Root::GetInstance();

  SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
  SDL_Color backgroundColor =
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
