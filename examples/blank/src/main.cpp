#define SDL_MAIN_HANDLED

#include "PaceLib.h"

using namespace PaceLib;


Window *win = nullptr;

Configuration* conf = nullptr;


bool init(int argc, const char *argv[])
{
	bool success = true;

	ConLog::Info("Initialization");

	ConLog::Info("Loading configuration");
	conf = new Configuration("conf.json");

	win = new Window(conf);
	Window::SetDrawColor({10, 10 , 90});
				
	return success;
}

bool start()
{
	ConLog::Info("Start");

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
		}

		win->Clear();

		win->Present();

	}

    return 0;
}
