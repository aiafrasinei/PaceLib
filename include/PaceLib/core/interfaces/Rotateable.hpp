#pragma once

namespace PaceLib {

class Rotateable {
 public:
  virtual void SetAngle(double angle) = 0;
  virtual double GetAngle() = 0;

 private:
 protected:
};

}