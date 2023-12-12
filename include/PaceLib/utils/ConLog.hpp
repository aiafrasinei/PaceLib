#pragma once

#include <string>

/* LOGLEVEL - message */
class ConLog {
public:
  static void SetTimeFormat(std::string format);

  static void Info(std::string message);
  static void Warn(std::string message);
  static void Error(std::string message);

  static void Custom(std::string level, std::string message);

private:
  static std::string format;
};