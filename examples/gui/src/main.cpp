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

	Tab::BeginBlock("first");
		Label::Begin("label");
		Button::Begin("start");
		Button::Begin("exit");
	Tab::EndBlock();
	
	root->GetTab("first")->GetButton("exit")->onClickCallback = []() {
		Window::running = false;
    };

	Tab::BeginBlock("second");
		Text::Begin("text");
		Label::BeginBlock("out");
			Tooltip::Begin("outo");
		Label::EndBlock();
		TextArea::Begin("texta");
		TextInput::Begin("in");
		CheckBox::Begin("test");
	Tab::EndBlock();

	Tabber::BeginBlock("third");
		Tabber::BeginTabBlock("Main");
			Button::Begin("third_tb_start");
		Tabber::EndTabBlock();

		Tabber::BeginTabBlock("Options");
			CheckBox::Begin("fullscreen");
			CheckBox::Begin("vsync");
		Tabber::EndTabBlock();

		Tabber::BeginTabBlock("Help");
			TextArea::Begin("third_tb_text");
		Tabber::EndTabBlock();
	Tabber::EndBlock();
	
	Label::Begin("out1");
	Button::Begin("astart");

	ButtonTex::Begin("gfx0");
	root->GetButtonTex("gfx0")->SetHighlightColor({10, 10, 10, 255});

	ButtonTex::Begin("gfx1");

	ComboBox::Begin("testcomb");
	root->GetComboBox("testcomb")->SetSelection(2);

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
