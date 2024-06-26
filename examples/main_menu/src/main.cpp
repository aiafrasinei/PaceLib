#define SDL_MAIN_HANDLED
#include "Init.hpp"

using namespace PaceLib;

Init *starter = nullptr;

bool init() {
  SDL_Log("Start");

  Root *root = starter->GetRoot();

  root->GetScene("Default")->GetTtfContainer()->Add(
      "font_title", "fonts/OpenSans_Condensed-Regular.ttf", 40, TTF_STYLE_NORMAL, 1);

  Text::Begin("title");
  Button::Begin("new");
  Button::Begin("options");
  Button::Begin("help");
  Button::Begin("exit");

  Button::Begin("back");
  root->GetButton("back")->Hide();

  root->GetButton("new")->mouseLeftButtonDownCallback = []() {};

  root->GetButton("options")->mouseLeftButtonDownCallback = [root]() {
    root->GetButton("back")->Show();
    root->GetButton("new")->Hide();
    root->GetButton("options")->Hide();
    root->GetButton("help")->Hide();
    root->GetButton("exit")->Hide();
  };

  root->GetButton("help")->mouseLeftButtonDownCallback = [root]() {
    root->GetButton("new")->Hide();
    root->GetButton("back")->Show();
    root->GetButton("options")->Hide();
    root->GetButton("help")->Hide();
    root->GetButton("exit")->Hide();
  };

  root->GetButton("exit")->mouseLeftButtonDownCallback = []() { Window::running = false; };

  root->GetButton("back")->mouseLeftButtonDownCallback = [root]() {
    root->GetButton("back")->Hide();
    root->GetButton("new")->Show();
    root->GetButton("options")->Show();
    root->GetButton("help")->Show();
    root->GetButton("exit")->Show();
  };

  return true;
}

int main(int argc, const char *argv[]) {
  starter = new Init();

  starter->onInit = &init;

  starter->Loop();

  return 0;
}
