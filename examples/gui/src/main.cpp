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

	conf = new Configuration("conf.json");

	win = new Window(conf);
				
	return success;
}

bool start()
{
	ConLog::Info("Start");
	
	root = &Root::GetInstance();
	root->SetCurrent(root);

	root->GetScene("Default")->AddTex("texs/sn_yellow.png", 0, 0, 512,512);
	root->GetScene("Default")->AddTex("texs/sn_yellow_border.png", 0, 0, 512,512);

	Tab::BeginBlock("first_tab");
		Label::Begin("label_lbl");
		Button::Begin("start_btn");
		Button::Begin("exit_btn");
	Tab::EndBlock();
	
	root->GetTab("first_tab")->GetButton("exit_btn")->onClickCallback = []() {
		Window::running = false;
    };

	Tab::BeginBlock("second_tab");
		Text::Begin("text");
		Label::BeginBlock("out_lbl");
			DefaultTooltip::Begin("out_tooltip");
		Label::EndBlock();
		TextArea::Begin("text_ta");
		TextInput::Begin("tinput");
		CheckBox::Begin("cb");
	Tab::EndBlock();

	Tabber::Begin("third_tb");
	root->GetTabber("third_tb")->AddTab("Main");
	root->GetTabber("third_tb")->AddTab("Options");
	root->GetTabber("third_tb")->AddTab("Help");

	Button::Begin({root->GetTabber("third_tb")->GetTab(0), "third_tb_start_btn"});
	CheckBox::Begin({root->GetTabber("third_tb")->GetTab(1), "fullscreen_cb"});
	CheckBox::Begin({root->GetTabber("third_tb")->GetTab(1), "vsync_cb"});
	TextArea::Begin({root->GetTabber("third_tb")->GetTab(2), "third_tb_text_ta"});
	
	Label::Begin("out1_lbl");
	Button::Begin("astart_btn");

	ButtonTex::Begin("gfx_button");
	root->GetButtonTex("gfx_button")->SetHighlightColor({10, 10, 10, 255});

	ButtonTex::Begin("gfx_button_tex");

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
