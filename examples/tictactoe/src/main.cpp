#define SDL_MAIN_HANDLED
#include "PaceLib.h"


using namespace PaceLib;

Window *win = nullptr;

Configuration* conf = nullptr;

Root *root;

int arr[3][3] = { {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
bool xSel = true;

bool init(int argc, const char *argv[])
{
	bool success = true;
	ConLog::Info("TicTacToe\n");

	ConLog::Info("Initialization");

	ConLog::Info("Loading configuration");
	conf = new Configuration("conf.json");

	win = new Window(conf);
				
	return success;
}

bool start()
{
	ConLog::Info("Start");

	root = &Root::GetInstance();
	root->SetCurrent(root);

	root->GetScene("Default")->GetFontContainer()->Add("ftext", "fonts/OpenSans_Condensed-Regular.ttf", 100, 0, 0, 0, 255);
	
	//Rectangle::Begin("border");

	Button::Begin("1b");
	Button::Begin("2b");
	Button::Begin("3b");

	Button::Begin("4b");
	Button::Begin("5b");
	Button::Begin("6b");

	Button::Begin("7b");
	Button::Begin("8b");
	Button::Begin("9b");

	root->GetButton("1b")->onClickCallback = []() {
		if(arr[0][0] == -1) {
			if(xSel) {
				arr[0][0] = 1;
				root->GetButton("1b")->SetText("X");
			} else {
				arr[0][0] = 0;
				root->GetButton("1b")->SetText("0");
			}
				
			xSel = !xSel;
		}
    };

	root->GetButton("2b")->onClickCallback = []() {
		if(arr[0][1] == -1) {
			if(xSel) {
				arr[0][1] = 1;
				root->GetButton("2b")->SetText("X");
			} else {
				arr[0][1] = 0;
				root->GetButton("2b")->SetText("0");
			}
				
			xSel = !xSel;
		}
    };

	root->GetButton("3b")->onClickCallback = []() {
		arr[0][2] = xSel;
		xSel = !xSel;
    };

	return true;
}

void stop()
{	
	delete win;

	ConLog::Info("Cleanup");
}

int main(int argc, const char *argv[])
{
    if(!init(argc, argv)) {
		stop();
		return 1;
	}
	
    if(!start()) {
		stop();
		return 2;
	}

	SDL_Event e;
	while(Window::running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				stop();
				return 0;
			}
			else if(e.type == SDL_KEYDOWN)
			{ 
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						stop();
						return 0;

					default:	
						break;
				}
			}

			root->Update(&e);
		}

		win->Clear();

		root->Draw();

		win->Present();

	}

	stop();

    return 0;
}
