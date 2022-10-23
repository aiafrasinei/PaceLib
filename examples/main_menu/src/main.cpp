#define SDL_MAIN_HANDLED
#include "PaceLib.h"
#include "graphics/gui/Texture.h"


using namespace PaceLib;

Window *win = nullptr;

Configuration* conf = nullptr;

Root *root;

bool init(int argc, const char *argv[])
{
	bool success = true;
	ConLog::Info("Game\n");

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

	root->GetScene("Default")->GetFontContainer()->Add("font_title", "fonts/OpenSans_Condensed-Regular.ttf", 40, 0, 0, 0, 255);

	Text::Begin("title");
	Button::Begin("new");
	Button::Begin("options");
	Button::Begin("help");
	Button::Begin("exit");

	Button::Begin("back");
	root->GetButton("back")->Hide();

	root->GetButton("new")->onClickCallback = []() {
    };

	root->GetButton("options")->onClickCallback = []() {
		root->GetButton("back")->Show();
		root->GetButton("new")->Hide();
		root->GetButton("options")->Hide();
		root->GetButton("help")->Hide();
		root->GetButton("exit")->Hide();
    };

	root->GetButton("help")->onClickCallback = []() {
		root->GetButton("new")->Hide();
		root->GetButton("back")->Show();
		root->GetButton("options")->Hide();
		root->GetButton("help")->Hide();
		root->GetButton("exit")->Hide();
    };

	root->GetButton("exit")->onClickCallback = []() {
		Window::running = false;
    };

	root->GetButton("back")->onClickCallback = []() {
		root->GetButton("back")->Hide();
		root->GetButton("new")->Show();
		root->GetButton("options")->Show();
		root->GetButton("help")->Show();
		root->GetButton("exit")->Show();
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
