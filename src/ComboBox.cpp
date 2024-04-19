#include <algorithm>
#include "ComboBox.h"
#include "Root.h"
#include "Triangle.h"

using namespace PaceLib;

ComboBox::ComboBox(ShapeId sid, MultiItemsProp prop) {
  this->prop = prop;

  rect = prop.rect;

  if (sid.parent->name != "root") {
    rect.x = sid.parent->GetRect().x + prop.rect.x;
    rect.y = sid.parent->GetRect().y + prop.rect.y;
  }

  this->prop.rect = rect;

  hidden = false;

  mouseOver = false;

  wtype = WidgetType::COMBOBOX;

  textSize = 0;

  selected = -1;
  mainRendererSelected = false;
  this->name = sid.name;
}

ComboBox::~ComboBox() {}

void ComboBox::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_ComboBox.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    float dim[4];
    Root::ParseDim(dim, conf);

    Root *root = &Root::GetInstance();

    std::string font = conf->Get("font").get<std::string>();
    SDL_FRect dimr = {dim[0], dim[1], dim[2], dim[3]};
    SDL_Color backgroundColor =
        Widget::ParseVar("background", conf, root->GetVars());
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
    SDL_Color highlightColor =
        Widget::ParseVar("highlight", conf, root->GetVars());

    SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());
    std::vector<std::string> tarr =
        conf->Get("text_arr").get<std::vector<std::string>>();

    MultiItemsProp prop = { conf->Get("scene").get<std::string>(), font,
        dimr, tarr, textColor, backgroundColor,
        borderColor, highlightColor};

    ComboBox *newcb = new ComboBox(sid, prop);

    sid.parent->Add(newcb);

    newcb->AddItems(tarr);
  }
}

void ComboBox::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  ComboBox::Begin({root->GetCurrent(), name});
}

void ComboBox::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  ComboBox::Begin({root->GetCurrent(), name});
  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void ComboBox::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void ComboBox::Begin(ShapeId sid, MultiItemsProp prop) {
  ComboBox *newcb = new ComboBox(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(newcb);

  ComboBox *combo = ((ComboBox *)root->GetCurrent()->Get(sid.name));
  combo->AddItems(prop.tarr);
}

void ComboBox::Draw() {
  for (Shape *w : shapes) {
    w->Draw();
  }
}

void ComboBox::Update(SDL_Event *e) {
  for (Shape *s : shapes) {
    s->Update(e);
  }
}

void ComboBox::InternalInit() {
  Root *root = &Root::GetInstance();

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *current = root->GetCurrent();

  Triangle::Begin({root->GetCurrent(), "triangle_decorator"},
                  {root->GetCurrentAbsoluteCoords().x,
                   root->GetCurrentAbsoluteCoords().y + this->GetRect().h,
                   root->GetCurrentAbsoluteCoords().x + this->GetRect().w,
                   root->GetCurrentAbsoluteCoords().y + this->GetRect().h,
                   root->GetCurrentAbsoluteCoords().x + this->GetRect().w / 2,
                   root->GetCurrentAbsoluteCoords().y + this->GetRect().h +
                       this->GetRect().h / 3,
                   /*prop.borderColor*/ {1.0, 1.0, 1.0, 1.0}});

  for (int i = 0; i < items.size(); i++) {
    SDL_FRect r = {root->GetCurrentAbsoluteCoords().x,
                  root->GetCurrentAbsoluteCoords().y + (i * this->GetRect().h),
                  this->GetRect().w, this->GetRect().h};
    LabelProp prop = {
        this->prop.scene,
        this->prop.font,
        r,
        items[i],
        this->prop.textColor,
        {H::MID},
        this->prop.backgroundColor,
        this->prop.borderColor,
        this->prop.highlightColor};

    Button::Begin({root->GetCurrent(), "item_" + std::to_string(i)}, prop);
    root->GetCurrent()->Get("item_" + std::to_string(i))->Hide();
  }

  LabelProp prop = {this->prop.scene, this->prop.font,
                    {root->GetCurrentAbsoluteCoords().x,
                     root->GetCurrentAbsoluteCoords().y, this->GetRect().w,
                     this->GetRect().h},
                    "",
                    this->prop.textColor,
                    {H::MID},
                    this->prop.backgroundColor,
                    this->prop.borderColor,
                    this->prop.highlightColor};

  Button::Begin({root->GetCurrent(), "main_item_renderer"}, prop);

  Button *main_renderer =
      ((Button *)root->GetCurrent()->Get("main_item_renderer"));
  main_renderer->mouseLeftButtonUpCallback = [this, main_renderer, root, current]() {
    mainRendererSelected = !mainRendererSelected;
    if (mainRendererSelected) {
      if (items.size() > 0) {
        main_renderer->Hide();
        for (int i = 0; i < items.size(); i++) {
          current->Get("item_" + std::to_string(i))->Show();
        }
      }
    } else {
      main_renderer->Show();
    }
  };

  for (int i = 0; i < items.size(); i++) {
    Button *currentb =
        ((Button *)root->GetCurrent()->Get("item_" + std::to_string(i)));
    currentb->mouseLeftButtonUpCallback = [this, i, main_renderer, current, currentb,
                                 root]() {
      for (int i = 0; i < items.size(); i++) {
        current->Get("item_" + std::to_string(i))->Hide();
      }
      mainRendererSelected = false;

      selected = i;
      main_renderer->SetText(currentb->GetProp()->text);
      main_renderer->Show();
    };
  }

  root->SetCurrent(prevParent);
}

int ComboBox::GetSelected() { return selected; }

void ComboBox::SetSelection(int index) {
  selected = index;

  Button *main_renderer = ((Button *)this->Get("main_item_renderer"));
  Button *sel = ((Button *)this->Get("item_" + std::to_string(selected)));

  if (items.size() > 0) {
    main_renderer->SetText(sel->GetProp()->text);
  }
}

int ComboBox::GetNrItems() { return items.size(); }

void ComboBox::AddItem(std::string item) {
  items.push_back(item);
  InternalInit();
}

void ComboBox::AddItems(std::vector<std::string> items) {
  for (int i = 0; i < items.size(); i++) {
    this->items.push_back(items[i]);
  }
  InternalInit();
}

void ComboBox::ReplaceItems(std::vector<std::string> items) {
  this->items = items;
  InternalInit();
}
