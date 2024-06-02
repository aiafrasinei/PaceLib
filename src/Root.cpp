#include "Root.hpp"

using namespace PaceLib;

Root::Root() {
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;

  hidden = false;

  name = "root";

  scenes["Default"] =
      new Scene("Default", Window::GetWindow(), Window::GetRenderer());
  scenes["Default"]->GetTtfContainer()->Add(
      "default", "fonts/OpenSans_Condensed-Regular.ttf", 20, TTF_STYLE_NORMAL,
      0);

  wtype = WidgetType::ROOT;

  if (std::filesystem::exists("wconfs/vars")) {
    vars = new Configuration("wconfs/vars");
  }

  currentAbsoluteCoords = {0, 0};
}

void Root::Draw() {
  SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r,
                         Window::GetBackgroundColor().g,
                         Window::GetBackgroundColor().b,
                         Window::GetBackgroundColor().a);

  if (this->state != nullptr) {
    this->state->Loop();
  }

  for (Shape *w : shapes) {
    w->Draw();
  }

  SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r,
                         Window::GetBackgroundColor().g,
                         Window::GetBackgroundColor().b,
                         Window::GetBackgroundColor().a);
}

void Root::Add(Shape *s) { shapes.push_back(s); }

Button *Root::GetButton(std::string child) {
  return static_cast<Button *>(this->Get(child));
}

ButtonTex *Root::GetButtonTex(std::string child) {
  return static_cast<ButtonTex *>(this->Get(child));
}

Label *Root::GetLabel(std::string child) {
  return static_cast<Label *>(this->Get(child));
}

Widget *Root::GetWidget(std::string child) {
  return static_cast<Widget *>(this->Get(child));
}

Tab *Root::GetTab(std::string child) {
  return static_cast<Tab *>(this->Get(child));
}

Tabber *Root::GetTabber(std::string child) {
  return static_cast<Tabber *>(this->Get(child));
}

Hotspot *Root::GetHotspot(std::string child) {
  return static_cast<Hotspot *>(this->Get(child));
}

Text *Root::GetText(std::string child) {
  return static_cast<Text *>(this->Get(child));
}

Tooltip *Root::GetTooltip(std::string child) {
  return static_cast<Tooltip *>(this->Get(child));
}

CheckBox *Root::GetCheckBox(std::string child) {
  return static_cast<CheckBox *>(this->Get(child));
}

TextInput *Root::GetTextInput(std::string child) {
  return static_cast<TextInput *>(this->Get(child));
}

TextArea *Root::GetTextArea(std::string child) {
  return static_cast<TextArea *>(this->Get(child));
}

ComboBox *Root::GetComboBox(std::string child) {
  return static_cast<ComboBox *>(this->Get(child));
}

Texture *Root::GetTexture(std::string child) {
  return static_cast<Texture *>(this->Get(child));
}

void Root::Update(SDL_Event *e) {
  for (Shape *s : shapes) {
    s->Update(e);
  }
}

void Root::SetState(State *state) {
  this->state = state;
  this->state->Execute();
}

std::map<std::string, Scene *> Root::GetScenes() { return scenes; }

Scene *Root::GetScene(std::string name) { return scenes[name]; }

void Root::HideAll() {
  for (Shape *s : shapes) {
    s->Hide();
  }
}

void Root::AddScene(std::string name) {
  scenes[name] = new Scene(name, Window::GetWindow(), Window::GetRenderer());
}

void Root::RemoveScene(std::string name) {
  delete scenes[name];
  scenes.erase(name);
}

Configuration *Root::GetVars() { return vars; }

bool Root::IsVarDefined(std::string name) {
  bool ret = false;

  if (vars->Get(name) != nullptr) {
    ret = true;
  }

  return ret;
}

void Root::ParseRect(std::string name, int dim[4], Configuration *conf) {
  Root *root = &Root::GetInstance();
  SDL_Rect r = static_cast<Widget *>(root->GetCurrent())->GetRect();

  for (int i = 0; i < 4; i++) {
    std::string str = conf->Get(name.c_str())[i].get<std::string>();
    std::string first_char = str.substr(0, 1);

    float val = 0;
    if (str == "W") {
      val = Window::width;
    } else if (str == "H") {
      val = Window::height;
    } else if (first_char == "W" || first_char == "H") {
      std::size_t pos = str.find("%");
      if (pos != std::string::npos) {
        if (first_char == "W")
          val = Window::width * std::stoi(str.substr(2, pos)) / 100;
        if (first_char == "H")
          val = Window::height * std::stoi(str.substr(2, pos)) / 100;
      }
    } else if (str == "#W") {
      val = r.w;
    } else if (str == "#H") {
      val = r.h;
    } else if (first_char == "#") {
      std::string second_char = str.substr(1, 1);
      if (second_char == "W" || second_char == "H") {
        std::size_t pos = str.find("%");
        if (pos != std::string::npos) {
          if (second_char == "W")
            val = r.w * std::stoi(str.substr(3, pos)) / 100;
          if (second_char == "H")
            val = r.h * std::stoi(str.substr(3, pos)) / 100;
        }
      }
    } else {
      val = std::stof(str);
    }

    dim[i] = val;
  }
}
