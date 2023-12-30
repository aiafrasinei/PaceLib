#define SDL_MAIN_HANDLED
#include "Init.hpp"

using namespace PaceLib;

Init *starter = nullptr;

int arr[][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

static bool xSel = true;
static int b_index = 1;
static bool gwin = false;

bool win_check() {
  bool ret = false;

  for (int i = 0; i < 3; i++) {
    int nrhx = 0, nrh0 = 0;
    int nrvx = 0, nrv0 = 0;

    for (int j = 0; j < 3; j++) {
      if (arr[i][j] == 1) {
        nrhx++;
      } else if (arr[i][j] == 0) {
        nrh0++;
      }

      if (arr[j][i] == 1) {
        nrvx++;
      } else if (arr[j][i] == 0) {
        nrv0++;
      }
    }

    if ((nrhx == 3 || nrh0 == 3) || (nrvx == 3 || nrv0 == 3)) {
      ret = true;
      break;
    }
  }

  if (arr[0][0] == 1 && arr[1][1] == 1 && arr[2][2] == 1)
    ret = true;

  if (arr[0][0] == 0 && arr[1][1] == 0 && arr[2][2] == 0)
    ret = true;

  if (arr[0][2] == 1 && arr[1][1] == 1 && arr[2][0] == 1)
    ret = true;

  if (arr[0][2] == 0 && arr[1][1] == 0 && arr[2][0] == 0)
    ret = true;

  return ret;
}

void reset_game(int arr[3][3]) {
  Root *root = starter->GetRoot();

  static int b_index = 1;
  static bool gwin = false;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arr[i][j] = -1;
    }
  }

  for (int i = 1; i < 10; i++) {
    root->GetButton(std::to_string(i) + "b")->SetText("");
  }

  xSel = !xSel;
}

void on_click(Root *root, int arr[3][3], int bindex, int i, int j) {
  if (arr[i][j] == -1) {
    std::string bindexs = std::to_string(bindex);
    if (xSel) {
      arr[i][j] = 1;
      root->GetButton(bindexs + "b")->SetText("X");
    } else {
      arr[i][j] = 0;
      root->GetButton(bindexs + "b")->SetText("0");
    }

    xSel = !xSel;
  }

  if (win_check()) {
    gwin = true;
    reset_game(arr);
  }
}

bool init() {
  SDL_Log("Start");

  Root *root = starter->GetRoot();

  root->GetScene("Default")->GetFontContainer()->Add(
      "ftext", "fonts/OpenSans_Condensed-Regular.ttf", 100, {0, 0, 0, 255});

  for (int i = 0; i < 10; i++) {
    std::string bis = std::to_string(i);
    Button::Begin(bis + "b");
  }

  root->GetButton("1b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 1, 0, 0);
  };

  root->GetButton("2b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 2, 0, 1);
  };

  root->GetButton("3b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 3, 0, 2);
  };

  root->GetButton("4b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 4, 1, 0);
  };

  root->GetButton("5b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 5, 1, 1);
  };

  root->GetButton("6b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 6, 1, 2);
  };

  root->GetButton("7b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 7, 2, 0);
  };

  root->GetButton("8b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 8, 2, 1);
  };

  root->GetButton("9b")->mouseLeftButtonDownCallback = [root]() {
    on_click(root, arr, 9, 2, 2);
  };

  return true;
}

int main(int argc, const char *argv[]) {
  starter = new Init();

  starter->onInit = &init;

  starter->Loop();

  return 0;
}
