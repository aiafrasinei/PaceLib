#include "TextInput.h"
#include "Root.h"

using namespace PaceLib;

TextInput::TextInput(ShapeId sid, LabelProp prop) : Label(sid, prop) {
  wtype = WidgetType::TEXTINPUT;

  this->focus = false;

  textSize = 0;
}

TextInput::~TextInput() {}

void TextInput::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_TextInput.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    LabelProp prop = LoadLabelProp(conf);

    TextInput *ti = new TextInput(sid, prop);
    sid.parent->Add(ti);

    ti->InternalInit();
  }
}

void TextInput::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  TextInput::Begin({root->GetCurrent(), name});
}

void TextInput::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  TextInput::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);

  Shape *c = root->GetCurrent();
  root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void TextInput::EndBlock() {
  Root *root = &Root::GetInstance();

  Shape *c = root->GetCurrent();
  root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

  root->SetCurrent(root->GetCurrent()->GetParent());
}

void TextInput::Begin(ShapeId sid, LabelProp prop) {
  TextInput *ti = new TextInput(sid, prop);

  Root *root = &Root::GetInstance();
  root->GetCurrent()->Add(ti);

  ((TextInput *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

void TextInput::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r,
                           prop.backgroundColor.g, prop.backgroundColor.b,
                           prop.backgroundColor.a);
    SDL_RenderFillRect(Window::GetRenderer(), &rect);

    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r,
                           prop.borderColor.g, prop.borderColor.b,
                           prop.borderColor.a);
    SDL_RenderDrawRect(Window::GetRenderer(), &rect);

    for (Shape *w : shapes) {
      w->Draw();
    }
  }
}

void TextInput::Update(SDL_Event *e) {
  if (focus) {
    Text *to = (Text *)this->Get(name + "_text");
    if (e->type == SDL_TEXTINPUT) {
      to->SetText(to->GetText() + e->text.text);
    }

    if (e->type == SDL_KEYDOWN) {
      char keyDown = e->key.keysym.scancode;
      if (keyDown == SDL_SCANCODE_BACKSPACE) {
        to->SetText(to->GetText().substr(0, to->GetText().size() - 1));
      }
    }
  }

  if (e->type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (PointInRect({x, y}, rect)) {
      focus = !focus;
    } else {
      focus = false;
    }
  }

  for (Shape *s : shapes) {
    s->Update(e);
  }
}

void TextInput::InternalInit() {
  // child text
  Root *root = &Root::GetInstance();
  TextInput *tin = (TextInput *)root->GetCurrent()->Get(name);

  TextProp tprop = {"Default", "default", GetRect().x + GetRect().w / 20, GetRect().y, nullptr,
                    prop.text, prop.textColor};

  Text::Begin({tin, tin->name + "_text"}, tprop);

  Text *to = (Text *)tin->Get(name + "_text");
  to->GetProp()->color = prop.textColor;
  textSize = to->GetWidth();

  to->SetX(GetRect().x + rect.w / 20);
  to->SetY(GetRect().y);
}
