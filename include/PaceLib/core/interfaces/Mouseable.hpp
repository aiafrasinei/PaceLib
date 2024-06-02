#pragma once

#include <functional>

namespace PaceLib {

class Mouseable {

public:
  std::function<void(void)> mouseLeftButtonDownCallback;

  std::function<void(void)> mouseLeftButtonUpCallback;

  std::function<void(void)> mouseRightButtonDownCallback;

  std::function<void(void)> mouseRightButtonUpCallback;

};

}