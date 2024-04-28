#include "ButtonGrid.hpp"
#include "Root.hpp"

using namespace PaceLib;

ButtonGrid::ButtonGrid(ShapeId sid, ButtonGridProp inputProp) {
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

ButtonGrid::ButtonGrid() {}

ButtonGrid::~ButtonGrid() {}

void ButtonGrid::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_ButtonGrid.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    ButtonGridProp prop = LoadButtonGridProp(conf);

    ButtonGrid *newg = new ButtonGrid(sid, prop);

    sid.parent->Add(newg);

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        ButtonTexProp p = {{nullptr,
                          {prop.rect.x + i * (prop.rect.w + prop.distance),
                           prop.rect.y + j * (prop.rect.w + prop.distance),
                           prop.rect.w, prop.rect.h}},
                         {nullptr,
                          {prop.rect.x + i * (prop.rect.w + prop.distance),
                           prop.rect.y + j * (prop.rect.w + prop.distance),
                           prop.rect.w, prop.rect.h}},
                         {100, 100, 100, 255},
                         {0, 0, 0, 255},
                         {120, 120, 120, 255},
                         false};

        Root *root = &Root::GetInstance();
        ButtonTex::Begin({root->GetCurrent(), sid.name + "_" + std::to_string(j) +
                                                "_" + std::to_string(i)}, p);
    }
  }
  }
}

void ButtonGrid::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  ButtonGrid::Begin({root->GetCurrent(), name});
}

void ButtonGrid::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  ButtonGrid::Begin({root->GetCurrent(), name});
  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void ButtonGrid::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void ButtonGrid::Begin(ShapeId sid, ButtonGridProp prop) {
  ButtonGrid *newb = new ButtonGrid(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(newb);
}

void ButtonGrid::Draw() {
  if (!hidden) {
    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

ButtonGridProp ButtonGrid::LoadButtonGridProp(Configuration *conf) {
  float dim[4];
  Root::ParseDim(dim, conf);

  HorizontalAlign align;
  if (conf->Get("align") == "left")
    align.halign = H::LEFT;
  else if (conf->Get("align") == "mid")
    align.halign = H::MID;
  else if (conf->Get("align") == "right")
    align.halign = H::RIGHT;

  Root *root = &Root::GetInstance();

  SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};
  std::string font = conf->Get("font").get<std::string>();
  std::string scene = conf->Get("scene").get<std::string>();
  float distance = conf->Get("distance").get<float>();

  ButtonGridProp prop = {scene, font, dimr, distance};
  return prop;
}