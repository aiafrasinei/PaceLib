#define SDL_MAIN_HANDLED
#include "PaceLib.h"


using namespace PaceLib;


Window *win = nullptr;
Scene *test_scene = nullptr;
Configuration* conf = nullptr;
Root *root;
ScrollingBackground *scroll_background;

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

	test_scene = new Scene("test", win->GetWindow(), win->GetRenderer());
	test_scene->AddTex("data/texs/test_room_x90_1.png", 400, 400, w/2, h/2);
	test_scene->AddFont("lazy_font", "fonts/lazy.ttf", 20, 0, 0, 0, 255);
	test_scene->AddTex("data/texs/bg.png", 0, 0, 400, 400);

	root = &Root::GetInstance();
	root->GetScene("Default").GetFontContainer()->Add("default", "fonts/OpenSans_Condensed-Regular.ttf", 20, 0, 0, 0, 255);

	Line::Create("line", root, 200, 100 , 300 , 200, { 50, 100, 50, 255 } );

	HorizontalLine::Create("hline", root, 400, 200, 100, { 50, 100, 150, 255 });

	VerticalLine::Create("vline", root, 350, 300, 50, { 150, 150, 150, 255 });

	Triangle::Create("tri", root, 0, 0, 150, 0, 150, 150, { 50, 100, 50, 255 } );
	root->Get("tri")->SetDrawType(DrawTypes::FILLED);

	Rectangle::Create("rect1", root, { 500, 300, 200, 200 } , { 100, 50, 50, 255 } );
	root->Get("rect1")->SetDrawType(DrawTypes::FILLED);

	Circle::Create("cir1", root, 200, 100, 30, { 20, 20, 50, 255 });
	Circle::Create("cir2", root, 400, 100, 30, { 50, 50, 70, 255 });
	root->Get("cir2")->SetDrawType(DrawTypes::FILLED);

	Text::Create({root, "text"}, 600, 100, {50, 50, 50, 255}, "some text");

	Pentagon::Create("penta", root, 100, 200, 150, 200, 200, 350, 70, 320, 50, 230, {150, 50, 50, 255 } );
	root->Get("penta")->SetDrawType(DrawTypes::FILLED);

	Sprite::Create("sprite", root, test_scene->GetTex(0), {750, 150, 150, 150 } );

	//Hexagon::Create("hexa", root, 100, 300, 150, 300, 200, 450, 70, 420, 50, 330, 200, 200, {150, 50, 50, 255 } );
	//root->Get("hexa")->SetDrawType(DrawTypes::FILLED);

	//Ellipse::Create("el", root, 400, 150, 70, 20);
	
	scroll_background = ScrollingBackground::Create(test_scene->GetTex(1), { 0, 0, w, h } );

	//Texture::Create({root, "background_tex"}, test_scene->GetTex(1), { 0, 0, 100, 500} );


	return true;
}

void stop()
{	
	test_scene->GetFontContainer()->Remove(0);
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

			test_scene->Update(&e);
		}

		win->Clear();


		float timeStep = stepTimer.GetTicks() / 1000.f;
		//ConLog::Info("timeStep: " + to_string(timeStep));
		
		scroll_background->Draw(timeStep);

		stepTimer.Start();

		test_scene->Draw();

		root->Draw();

		win->Present();

	}

    return 0;
}