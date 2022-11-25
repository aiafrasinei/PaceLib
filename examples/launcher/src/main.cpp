#define SDL_MAIN_HANDLED
#include "core/Init.hpp"

using namespace PaceLib;


Init *starter = nullptr;

bool init()
{
	Root *root = starter->GetRoot();

	Tabber::BeginBlock("Bag");
		Tabber::BeginTabBlock("Main");
			Button::Begin("new_game");
			Button::Begin("credits");
			Button::Begin("exit");
		Tabber::EndTabBlock();

		Tabber::BeginTabBlock("Settings");
			CheckBox::Begin("fullscreen");
			CheckBox::Begin("vsync");
		Tabber::EndTabBlock();

		Tabber::BeginTabBlock("Help");
			TextArea::Begin("help");
		Tabber::EndTabBlock();
	Tabber::EndBlock();

	root->GetTabber("Bag")->GetTab(0)->GetButton("exit")->onClickCallback = []() {
		Window::running = false;
    };

	return true;
}

int main(int argc, const char *argv[])
{
	starter = new Init();

	starter->onInit = &init;
	
	starter->Loop();

    return 0;
}
