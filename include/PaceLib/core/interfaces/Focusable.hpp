#pragma once

namespace PaceLib {

class Focusable {

public:
  bool IsFocused() { return focus; }

  void Focus() { focus = true; }

  void Unfocus() { focus = false; }

protected:
  bool focus;
};

}