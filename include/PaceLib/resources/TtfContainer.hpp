#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "TexContainer.hpp"
#include "utils/Platform.hpp"

namespace PaceLib {

class TtfContainer {
 public:
  TtfContainer(std::string name);
  ~TtfContainer();

  bool Add(std::string name, std::filesystem::path file_path, int size,
           int style, int outline);

  void Remove(std::string name);

  TTF_Font *Get(std::string name);

  std::string GetName();
  void ChangeName(std::string name);

 protected:
 private:
  std::map<std::string, TTF_Font *> container;
  std::string name;
};

}  // namespace PaceLib
