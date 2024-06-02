#pragma once

namespace PaceLib {

class State {
 public:
  virtual ~State(){};
  virtual void Execute(){};
  virtual void Loop(){};
};

}