#pragma once

namespace PaceLib {

class Hidable {

public:
  bool IsHidden() { return hidden; }

  void Hide() { hidden = true; }

  void Show() { hidden = false; }

protected:
  bool hidden;
};

}