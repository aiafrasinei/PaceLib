#include "ButtonTexGrid.hpp"

#include "Root.hpp"

using namespace PaceLib;

ButtonTexGrid::ButtonTexGrid(ShapeId sid, ButtonTexGridProp inputProp) {
  prop = inputProp;

  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  prop.rect = rect;

  hidden = false;

  name = sid.name;

  wtype = WidgetType::BUTTONGRID;
}

void ButtonTexGrid::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_ButtonGrid.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    ButtonTexGridProp prop = LoadButtonTexGridProp(conf);

    ButtonTexGrid *newg = new ButtonTexGrid(sid, prop);

    sid.parent->Add(newg);

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        ButtonTexProp p = {{prop.normal.tex,
                            {prop.rect.x + i * (prop.rect.w + prop.distance),
                             prop.rect.y + j * (prop.rect.w + prop.distance),
                             prop.rect.w, prop.rect.h}},
                           {prop.over.tex,
                            {prop.rect.x + i * (prop.rect.w + prop.distance),
                             prop.rect.y + j * (prop.rect.w + prop.distance),
                             prop.rect.w, prop.rect.h}},
                           prop.backgroundColor,
                           prop.borderColor,
                           prop.highlightColor,
                           prop.drawBorder};

        Root *root = &Root::GetInstance();
        ButtonTex::Begin(
            {root->GetCurrent(),
             sid.name + "_" + std::to_string(j) + "_" + std::to_string(i)},
            p);
      }
    }
  }
}

void ButtonTexGrid::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  ButtonTexGrid::Begin({root->GetCurrent(), name});
}

void ButtonTexGrid::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  ButtonTexGrid::Begin({root->GetCurrent(), name});
  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void ButtonTexGrid::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void ButtonTexGrid::Begin(ShapeId sid, ButtonTexGridProp prop) {
  ButtonTexGrid *newb = new ButtonTexGrid(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(newb);
}

void ButtonTexGrid::Draw() {
  if (!hidden) {
    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

ButtonTexGridProp ButtonTexGrid::LoadButtonTexGridProp(Configuration *conf) {
  int dim[4];
  Root::ParseRect("dim", dim, conf);

  HorizontalAlign align;
  if (conf->Get("align") == "left")
    align.halign = H::LEFT;
  else if (conf->Get("align") == "mid")
    align.halign = H::MID;
  else if (conf->Get("align") == "right")
    align.halign = H::RIGHT;

  Root *root = &Root::GetInstance();

  SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
  std::string scene = conf->Get("scene").get<std::string>();
  int distance = conf->Get("distance").get<int>();

  SDL_Color borderColor = {0, 0, 0, 255};
  bool drawBorder = true;
  if (conf->Get("border") == "")
    drawBorder = false;
  else
    borderColor = Widget::ParseVar("border", conf, root->GetVars());

  SDL_Color highlightColor =
      Widget::ParseVar("highlight", conf, root->GetVars());
  SDL_Color backgroundColor =
      Widget::ParseVar("background", conf, root->GetVars());

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

  ButtonTexGridProp prop = {scene,       dimr,           distance,
                            tex_prop,    over_tex_prop,  backgroundColor,
                            borderColor, highlightColor, drawBorder};
  return prop;
}

void ButtonTexGrid::SetScene(std::string scene) { prop.scene = scene; }
std::string ButtonTexGrid::GetScene() { return prop.scene; }

void ButtonTexGrid::SetDistance(int distance) { prop.distance = distance; }
int ButtonTexGrid::GetDistance() { return prop.distance; }

void ButtonTexGrid::SetNormal(TexProp normal) { prop.normal = normal; }
TexProp ButtonTexGrid::GetNormal() { return prop.normal; }

void ButtonTexGrid::SetOver(TexProp over) { prop.over = over; }
TexProp ButtonTexGrid::GetOver() { return prop.over; }

void ButtonTexGrid::SetBackgroundColor(SDL_Color color) { prop.backgroundColor = color; }
SDL_Color ButtonTexGrid::GetBackgroundColor() { return prop.backgroundColor; }

void ButtonTexGrid::SetBorderColor(SDL_Color color) { prop.borderColor = color; }
SDL_Color ButtonTexGrid::GetBorderColor() { return prop.borderColor; }

void ButtonTexGrid::SetHighlightColor(SDL_Color color) { prop.highlightColor = color; }
SDL_Color ButtonTexGrid::GetHighlightColor() { return prop.highlightColor; }

void ButtonTexGrid::SetDrawBorder(bool drawBorder) { prop.drawBorder = drawBorder; }
bool ButtonTexGrid::GetDrawBorder() { return prop.drawBorder; }
