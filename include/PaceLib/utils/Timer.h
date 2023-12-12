#pragma once

namespace PaceLib {

class Timer {
public:
  Timer();
  ~Timer();

  void Start();
  void Stop();
  void Pause();
  void Unpause();

  unsigned int GetTicks();

  bool IsStarted();
  bool IsPaused();

private:
  unsigned int start_ticks;

  unsigned int paused_ticks;

  bool paused;
  bool started;
};

} // namespace PaceLib