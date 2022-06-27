#define SDL_MAIN_HANDLED
#include "PaceLib.h"
#include "graphics/gui/Texture.h"


using namespace PaceLib;

Window *win = nullptr;

Configuration* conf = nullptr;

Root *root;

void stop();

bool init(int argc, const char *argv[])
{
	bool success = true;
	ConLog::Info("Game\n");
	ConLog::Info("Pace Engine version " + std::string(PACE_VERSION));

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
	root->GetScene("Default").GetFontContainer()->Add("default", "fonts/OpenSans_Condensed-Regular.ttf", 20, 0, 0, 0, 255);
	root->GetScene("Default").GetFontContainer()->Add("font_title", "fonts/OpenSans_Condensed-Regular.ttf", 40, 0, 0, 0, 255);

	Random *rn = new Random();

	Text::Create({root, "title_txt"});

	Button::Create({root, "new_btn"});

	Button::Create({root, "options_btn"});

	Button::Create({root, "help_btn"});

	Button::Create({root, "exit_btn"});

	Button::Create({root, "back_btn"});
	root->GetButton("back_btn")->Hide();

	root->GetButton("new_btn")->onClickCallback = []() {
    };

	root->GetButton("options_btn")->onClickCallback = []() {
		root->GetButton("back_btn")->Show();
		root->GetButton("new_btn")->Hide();
		root->GetButton("options_btn")->Hide();
		root->GetButton("help_btn")->Hide();
		root->GetButton("exit_btn")->Hide();
    };

	root->GetButton("help_btn")->onClickCallback = []() {
		root->GetButton("new_btn")->Hide();
		root->GetButton("back_btn")->Show();
		root->GetButton("options_btn")->Hide();
		root->GetButton("help_btn")->Hide();
		root->GetButton("exit_btn")->Hide();
    };

	root->GetButton("exit_btn")->onClickCallback = []() {
		Window::running = false;
    };

	root->GetButton("back_btn")->onClickCallback = []() {
		root->GetButton("back_btn")->Hide();
		root->GetButton("new_btn")->Show();
		root->GetButton("options_btn")->Show();
		root->GetButton("help_btn")->Show();
		root->GetButton("exit_btn")->Show();
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
