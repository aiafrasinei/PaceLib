#define SDL_MAIN_HANDLED
#include "PaceLib.h"

using namespace PaceLib;


Window *win = nullptr;
Configuration* conf = nullptr;
Root *root;
ScrollingBackground *scroll_background;
Sprite *ex_sprite;

bool init(int argc, const char *argv[])
{
	bool success = true;

	ConLog::Info("Initialization");

	ConLog::Info("Loading configuration");
	conf = new Configuration("conf.json");

	win = new Window(conf);
				
	return success;
}

bool start()
{
	ConLog::Info("Start");
	
	int w,h;

	SDL_GetRendererOutputSize(win->GetRenderer(), &w, &h);
	SDL_RenderSetLogicalSize(win->GetRenderer(), w, h);

	root = &Root::GetInstance();
	
	root->GetScene("Default")->GetFontContainer()->Add("lazy_font", "fonts/lazy.ttf", 20, 0, 0, 0, 255);

	root->GetScene("Default")->AddTex("texs/test_room_x90_1.png", 400, 400, w/2, h/2);
	root->GetScene("Default")->AddTex("texs/bg.png", 0, 0, 400, 400);
	root->GetScene("Default")->AddTex("texs/sprite_sheet.png", 0, 0, 1500, 300);

	Line::Begin({root, "line"}, 200, 100 , 300 , 200, { 50, 100, 50, 255 } );

	Line::Begin({root, "hline"}, 400, 300, 300, 300, { 50, 100, 150, 255 });

	Line::Begin({root, "vline"}, 350, 350, 350, 400, { 50, 100, 150, 255 });

	Triangle::Begin({root, "tri"}, 0, 0, 150, 0, 150, 150, { 50, 100, 50, 255 } );

	Rectangle::Begin({root, "rect1"}, { 500, 300, 200, 200 } , { 100, 50, 50, 255 } );

	Circle::Begin({root, "cir1"}, 200, 100, 30, { 20, 20, 50, 255 });
	Circle::Begin({root, "cir2"}, 400, 100, 30, { 50, 50, 70, 255 });

	TextProp prop = { 600, 100, root->GetScene("Default")->GetFont("lazy_font"), "some text", {50, 50, 50, 255} };
	Text::Begin({root, "text"}, prop);

	Sprite::Begin({root, "sprite"}, root->GetScene("Default")->GetTex("sprite_sheet.png"), {400, 600, 300, 300 }, 300, 5);

	scroll_background = ScrollingBackground::Begin(root->GetScene("Default")->GetTex("bg.png"), { 0, 0, w, h } );

	Polygon::Begin({root, "poly"});

	Lines::Begin({root, "ln"});

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

	Timer stepTimer;

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

		}

		win->Clear();


		float timeStep = stepTimer.GetTicks() / 1000.f;
		//ConLog::Info("timeStep: " + to_string(timeStep));
		
		scroll_background->Draw(timeStep);

		stepTimer.Start();

		root->Draw();

		win->Present();

	}

    return 0;
}
