#define SDL_MAIN_HANDLED
#include "core/Init.hpp"

using namespace PaceLib;


Init *starter = nullptr;

bool init()
{
	Root *root = starter->GetRoot();

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
	//root->GetButtonTex("gfx0")->SetHighlightColor({10, 10, 10, 255});

	ButtonTex::Begin("gfx1");

	ComboBox::Begin("testcomb");
	root->GetComboBox("testcomb")->SetSelection(2);

	Hotspot::Begin("tes");

	return true;
}

void deinit()
{	

}

int main(int argc, const char *argv[])
{
	starter = new Init();

	starter->onInit = &init;
	starter->onDeinit = &deinit;
	
	starter->Loop();

    return 0;
}
