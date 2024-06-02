#pragma once

#include "../core/interfaces/Updateable.hpp"
#include "Text.hpp"
#include "Widget.hpp"

namespace PaceLib {

class ComboBox : public Widget {
 public:
  // static methods

  // json configuration

  /* Loads wconf file
  example format:
  {
      "scene" : "Default",
      "rect" : ["W_47%", "H_23%", "H_7.5%", "H_3%"],
      "color" : [100, 100, 70, 255],
      "font" : "default",
      "text" : "Start",
      "text_color" : [0, 0, 0, 255],
      "border" : [0, 0, 0, 255],
      "items" : ["test1", "test2", "test3", "test4", "test5"]
  }*/
  static void Begin(ShapeId sid);
  static void Begin(std::string name);

  // used when the button will have child elements
  static void BeginBlock(std::string name);
  static void EndBlock();

  // programmatic
  static void Begin(ShapeId sid, MultiItemsProp prop);

  ~ComboBox();

  void Draw();
  void Update(SDL_Event *e);

  int GetSelected();
  int GetNrItems();
  void SetSelection(int index);

  void AddItem(std::string item);
  void AddItems(std::vector<std::string> items);
  void ReplaceItems(std::vector<std::string> items);

  MultiItemsProp *GetProp() { return &prop; }

 private:
  ComboBox(ShapeId sid, MultiItemsProp inputProp);

  MultiItemsProp prop;

  bool mouseOver;

  int textSize;

  void InternalInit();

  std::vector<std::string> items;

  int selected;

  bool mainRendererSelected;
};
<<<<<<< HEAD
}  // namespace PaceLib
=======

}
>>>>>>> 68be932 (Rename dim to rect in the json configurations)
