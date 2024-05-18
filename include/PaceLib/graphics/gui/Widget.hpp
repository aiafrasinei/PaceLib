#pragma once

#include <functional>
#include <map>

#include "Props.hpp"
#include "Shape.hpp"

namespace PaceLib {

class Widget : public Shape {
 public:
  virtual void Draw() = 0;

  WidgetType GetWidgetType() { return wtype; }

  static void ParsePos(int pos[2], Configuration *conf) {
    for (int i = 0; i < 2; i++) {
      std::string str = conf->Get("pos")[i].get<std::string>();
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
      } else {
        val = std::stof(str);
      }

      pos[i] = val;
    }
  }

  static SDL_Color ParseVar(std::string key, Configuration *conf,
                            Configuration *vars) {
    SDL_Color color;

    if (conf->Get(key).is_string()) {
      std::string name = conf->Get(key).get<std::string>().substr(1);
      if (vars->Get(name) != nullptr) {
        color = {vars->Get(name)[0], vars->Get(name)[1], vars->Get(name)[2],
                 vars->Get(name)[3]};
      }
    } else {
      color = {conf->Get(key)[0], conf->Get(key)[1], conf->Get(key)[2],
               conf->Get(key)[3]};
    }

    return color;
  }

 protected:
  WidgetType wtype;
};

struct ShapeId {
  Shape *parent;
  std::string name;
};
}  // namespace PaceLib