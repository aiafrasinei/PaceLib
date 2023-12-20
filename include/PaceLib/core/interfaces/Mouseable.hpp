#pragma once

#include <functional>

class Mouseable {

public:
  std::function<void(void)> mouseLeftButtonDownCallback;

  std::function<void(void)> mouseLeftButtonUpCallback;

  std::function<void(void)> mouseRightButtonDownCallback;

  std::function<void(void)> mouseRightButtonUpCallback;
  
private:
protected:
};