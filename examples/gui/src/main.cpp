#define SDL_MAIN_HANDLED
#include "PaceLib.h"

using namespace PaceLib;


Window *win = nullptr;

Configuration* conf = nullptr;

Root *root;

bool init(int argc, const char *argv[])
{
	bool success = true;
	ConLog::Info("gui\n");

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

	root->GetScene("Default").AddTex("texs/sn_yellow.png", 0, 0, 512,512);
	root->GetScene("Default").AddTex("texs/sn_yellow_border.png", 0, 0, 512,512);

	Tab::Create( {root, "first_p"} , { {50, 50, 300, 300} , {70, 80, 90, 255} } );
	Label::Create( {root->GetTab("first_p"), "label_lbl"}, {10, 10 , 150, 30}, "Main Menu");
	Button::Create( {root->GetTab("first_p"), "start_btn"}, {10, 50 , 150, 30}, "Start");
	Button::Create( {root->GetTab("first_p"), "exit_btn"}, {10, 90, 150, 30}, "Exit" );
	
	root->GetTab("first_p")->GetButton("exit_btn")->onClickCallback = []() {
		Window::running = false;
    };

	Tab::Create( {root, "second_p"} , { {400, 50, 300, 350} , {80, 70, 80, 255} } );
	Text::Create({root->GetTab("second_p"), "text"}, 10, 10, {180, 180, 180, 255}, "Text text text");

	Label::Create( {root->GetTab("second_p"), "out_lbl"},
				{ {10, 50, 150, 30}, {100, 70, 70, 255} },
				{root->GetScene("Default").GetFont("default"), "colored label"},
				{V::MID, H::LEFT} );
	DefaultTooltip::Create( {root->GetTab("second_p")->GetLabel("out_lbl"), "out_tooltip"}, "this is a color label");

	TextArea::Create( {root->GetTab("second_p"), "text_ta"}, {{10, 100, 130, 130}, {70, 70, 80, 255}}, {"first", "second line", "third line"});

	TextInput::Create( {root->GetTab("second_p"), "tinput"}, {10, 250, 130, 30});

	CheckBox::Create( {root->GetTab("second_p"), "cb"}, {{10, 300, 20, 20}, {120, 120, 120, 255}}, "Checkbox");


	Tabber::Create( {root, "third_tb"} , { {50, 450, 300, 300}, {70, 80, 70, 255} });
	root->GetTabber("third_tb")->AddTab("Main");
	root->GetTabber("third_tb")->AddTab("Options");
	root->GetTabber("third_tb")->AddTab("Help");

	Button::Create( {root->GetTabber("third_tb")->GetTab(0), "start_btn"}, {5, 5 , 150, 30}, "Start");
	CheckBox::Create( {root->GetTabber("third_tb")->GetTab(1), "fullscreen"}, {{5, 5, 20, 20}, {120, 120, 120, 255}}, "Fullscreen");
	CheckBox::Create( {root->GetTabber("third_tb")->GetTab(1), "vsync"}, {{5, 30, 20, 20}, {120, 120, 120, 255}}, "Vsync");
	TextArea::Create( {root->GetTabber("third_tb")->GetTab(2), "text_ta"}, {{5, 5, 130, 130}, {70, 70, 80, 255}}, {"Help system", "how to play the game", "third line"});
	
	Label::Create( {root, "out1_lbl"}, { {750, 50, 250, 30}, {100, 100, 70, 255} },
			{root->GetScene("Default").GetFont("default"), "another label"},{V::MID, H::LEFT} );
	Button::Create( {root, "astart_btn"}, { {750, 100, 100, 30}, {100, 100, 70, 255} }, {root->GetScene("Default").GetFont("default"), "Start"}, {V::MID, H::LEFT});

	ButtonTex::Create({root, "gfx_button"});
	root->GetButtonTex("gfx_button")->SetHighlightColor({10, 10, 10, 255});

	ButtonTex::Create({root, "gfx_button_tex"});

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

    return 0;
}
