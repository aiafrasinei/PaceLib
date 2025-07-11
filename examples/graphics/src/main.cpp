#define SDL_MAIN_HANDLED
#include "Init.hpp"

using namespace PaceLib;

Init *starter = nullptr;

ScrollingBackground *scroll_background;
Sprite *ex_sprite;
Timer stepTimer;

bool init() {
  SDL_Log("Start");

  Root *root = starter->GetRoot();

  root->GetScene("Default")->GetTtfContainer()->Add(
      "lazy_font", "fonts/lazy.ttf", 20, TTF_STYLE_NORMAL, 1);

  root->GetScene("Default")->AddTex("texs/test_room_x90_1.png", 400, 400, Window::width / 2,
                                    Window::height / 2);
  root->GetScene("Default")->AddTex("texs/bg.png", 0, 0, 400, 400);
  root->GetScene("Default")->AddTex("texs/sprite_sheet.png", 0, 0, 1500, 300);

  Point::Begin({root, "point"}, {300.0, 10.0 , {255, 0.0, 0.0, 255} });

  Line::Begin({root, "line"}, {200, 100, 300, 200, {50, 100, 50, 255}});

  Line::Begin({root, "hline"}, {400, 300, 300, 300, {50, 100, 150, 255}});

  Line::Begin({root, "vline"}, {350, 350, 350, 400, {50, 100, 150, 255}});

  Triangle::Begin({root, "tri"}, {0, 0, 150, 0, 150, 150, {0.5, 1, 0.5, 1}});

  Rectangle::Begin({root, "rect1"}, {{500, 300, 200, 200}, {100, 50, 50, 255}});

  Circle::Begin({root, "cir1"}, {200, 100, 30, {20, 20, 50, 255}});
  Circle::Begin({root, "cir2"}, {400, 100, 30, {50, 50, 70, 255}});
  static_cast<Circle *>(root->Get("cir2"))->SetDrawType(DrawTypes::FILLED);

  TextProp prop = {.scene = "Default",
                   .font = "lazy_font",
                   .x = 600,
                   .y = 100,
                   .tex = nullptr,
                   .text = "some text",
                   .color = {150, 50, 50, 255}};
  Text::Begin({root, "text"}, prop);

  Sprite::Begin({root, "sprite"},
                {root->GetScene("Default")->GetTex("sprite_sheet.png"),
                 {400, 600, 300, 300},
                 300,
                 5});

  scroll_background = ScrollingBackground::Begin(
      root->GetScene("Default")->GetTex("bg.png"), {0, 0, (float)Window::width, (float)Window::height});

  Polygon::Begin({root, "poly"});

  Lines::Begin({root, "ln"});

  return true;
}

void draw() {
  float timeStep = stepTimer.GetTicks() / 1000.f;
  scroll_background->Draw(timeStep);
  stepTimer.Start();
}

int main(int argc, const char *argv[]) {
  starter = new Init();

  starter->onInit = &init;
  starter->onDraw = &draw;

  starter->Loop();

  return 0;
}
