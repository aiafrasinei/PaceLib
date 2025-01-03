#include "ButtonTex.hpp"

#include "Root.hpp"

using namespace PaceLib;

ButtonTex::ButtonTex(ShapeId sid, ButtonTexProp prop) {
  this->prop = prop;

  rect = prop.normal.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.normal.rect.x;
    rect.y = sid.parent->GetRect().y + prop.normal.rect.y;
  }

  this->prop.normal.rect = rect;

  hidden = false;

  this->name = sid.name;

  mouseOver = false;

  highlight = true;

  wtype = WidgetType::BUTTONTEX;
}

void ButtonTex::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_ButtonTex.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    ButtonTexProp prop = LoadButtonTexProp(conf);

    ButtonTex *btex = nullptr;
    TexProp nullp = {nullptr, {0, 0, 0, 255}};

    if (conf->Get("over_tex_name").get<std::string>() == "") {
      prop.over = nullp;
      btex = new ButtonTex(sid, prop);
    } else if (conf->Get("tex_name").get<std::string>() == "" &&
               conf->Get("over_tex_name").get<std::string>() == "") {
      prop.normal = nullp;
      prop.over = nullp;
      btex = new ButtonTex(sid, prop);
    } else {
      btex = new ButtonTex(sid, prop);
    }

    if (btex != nullptr) {
      btex->conf = conf;
      sid.parent->Add(btex);
    }
  }
}

void ButtonTex::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  ButtonTex::Begin({root->GetCurrent(), name});
}

void ButtonTex::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  ButtonTex::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void ButtonTex::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void ButtonTex::Begin(ShapeId sid, ButtonTexProp prop) {
  sid.parent->Add(new ButtonTex(sid, prop));
}

void ButtonTex::Draw() {
  if (!hidden) {
    if (mouseOver) {
      if (prop.normal.tex == nullptr) {
        if (prop.over.tex == nullptr) {
          SDL_SetRenderDrawColor(Window::GetRenderer(), prop.highlightColor.r,
                                 prop.highlightColor.g, prop.highlightColor.b,
                                 prop.highlightColor.a);
          SDL_RenderFillRect(Window::GetRenderer(), &rect);
        }
      } else {
        if (prop.over.tex == nullptr) {
          SDL_SetTextureColorMod(prop.normal.tex, prop.highlightColor.r,
                                 prop.highlightColor.g, prop.highlightColor.b);
          SDL_RenderTexture(Window::GetRenderer(), prop.normal.tex, nullptr,
                            &prop.normal.rect);
        } else {
          SDL_RenderTexture(Window::GetRenderer(), prop.over.tex, nullptr,
                            &prop.over.rect);
        }
      }
    } else {
      if (prop.normal.tex != nullptr) {
        SDL_SetTextureColorMod(prop.normal.tex, 255, 255, 255);
        SDL_RenderTexture(Window::GetRenderer(), prop.normal.tex, nullptr,
                          &prop.normal.rect);
      } else {
        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                               prop.backgroundColor.g, prop.backgroundColor.b,
                               prop.backgroundColor.a);
        SDL_RenderFillRect(Window::GetRenderer(), &rect);
      }
    }

    if (prop.drawBorder) {
      SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r,
                             prop.borderColor.g, prop.borderColor.b,
                             prop.borderColor.a);
      SDL_RenderRect(Window::GetRenderer(), &rect);
    }

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void ButtonTex::Update(SDL_Event *e) {
  if (!hidden) {
    float x, y;
    SDL_GetMouseState(&x, &y);

    UpdateMouse(e, x, y);

    if (highlight) {
      if (PointInRect({x, y}, rect)) {
        mouseOver = true;
      } else {
        mouseOver = false;
      }
    }
  }
}

void ButtonTex::SetHighlight(bool state) { highlight = state; }

void ButtonTex::SetBorder(bool state) { drawBorder = state; }

ButtonTexProp ButtonTex::LoadButtonTexProp(Configuration *conf) {
  float dim[4];
  Root::ParseRect("rect", dim, conf);

  SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};

  Root *root = &Root::GetInstance();

  SDL_FColor borderColor = {0, 0, 0, 255};
  bool drawBorder = true;
  if (conf->Get("border") == "")
    drawBorder = false;
  else
    borderColor = Widget::ParseVar("border", conf, root->GetVars());

  SDL_FColor highlightColor =
      Widget::ParseVar("highlight", conf, root->GetVars());
  SDL_FColor backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());

  ButtonTexProp prop;
  TexProp tex_prop;
  TexProp over_tex_prop;

  if (conf->Get("tex_name") == "" && conf->Get("over_tex_name") == "") {
    tex_prop = {nullptr, dimr};
    over_tex_prop = {nullptr, dimr};
  } else {
    if (conf->Get("over_tex_name") == "") {
      tex_prop = {
          root->GetScene(conf->Get("scene"))->GetTex(conf->Get("tex_name")),
          dimr};
      over_tex_prop = {};
    } else {
      tex_prop = {
          root->GetScene(conf->Get("scene"))->GetTex(conf->Get("tex_name")),
          dimr};
      over_tex_prop = {root->GetScene(conf->Get("scene"))
                           ->GetTex(conf->Get("over_tex_name")),
                       dimr};
    }
  }

  prop = {tex_prop,    over_tex_prop,  backgroundColor,
          borderColor, highlightColor, drawBorder};

  return prop;
}

void ButtonTex::SetNormal(TexProp normal) { prop.normal = normal; }
TexProp ButtonTex::GetNormal() { return prop.normal; }

void ButtonTex::SetOver(TexProp over) { prop.over = over; }
TexProp ButtonTex::GetOver() { return prop.over; }

void ButtonTex::SetBackgroundColor(SDL_FColor backgroundColor) {
  prop.backgroundColor = backgroundColor;
}
SDL_FColor ButtonTex::GetBackgroundColor() { return prop.backgroundColor; }

void ButtonTex::SetBorderColor(SDL_FColor borderColor) {
  prop.borderColor = borderColor;
}
SDL_FColor ButtonTex::GetBorderColor() { return prop.borderColor; }

void ButtonTex::SetHighlightColor(SDL_FColor highlightColor) {
  prop.highlightColor = highlightColor;
}
SDL_FColor ButtonTex::GetHighlightColor() { return prop.highlightColor; }
