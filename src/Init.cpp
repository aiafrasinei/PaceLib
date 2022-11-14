#include "Init.hpp"


using namespace PaceLib;

Init::Init()
{
	ConLog::Info("PaceLib Init");

	conf = new Configuration("conf.json");

	win = new Window(conf);

    root = &Root::GetInstance();
	root->SetCurrent(root);
}

Init::~Init()
{
    delete conf;
    delete root;
    delete win;
}

Root *Init::GetRoot()
{
    return root;
}

Window *Init::GetWindow()
{
    return win;
}

void Init::Loop()
{
    ConLog::Info("Init");
    onInit();

    SDL_Event e;
	while(Window::running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				Window::running = false;
			}

			root->Update(&e);
		}

		win->Clear();
		root->Draw();
		win->Present();
	}

    ConLog::Info("Deinit");
    onDeinit();
}