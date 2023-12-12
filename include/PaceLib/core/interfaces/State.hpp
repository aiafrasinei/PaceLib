#pragma once

class State {
public:
  virtual ~State(){};
  virtual void Execute(){};
  virtual void Loop(){};
};