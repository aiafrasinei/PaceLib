#define SDL_MAIN_HANDLED

#include "PaceLib.h"
using namespace PaceLib;


Window *win = nullptr;

Configuration* conf = nullptr;

SDL_Renderer *renderer = nullptr;

SDL_Vertex *v = nullptr;


bool init(int argc, const char *argv[])
{
	bool success = true;
	
	ConLog::Info("Initialization");

	ConLog::Info("Loading configuration");
	conf = new Configuration("conf.json");

	win = new Window(conf);

	renderer = win->GetRenderer();

	v = new SDL_Vertex[3];

	v[0].position.x = 400;
	v[0].position.y = 150;
	v[0].color = {255, 0, 0, 255};

	v[1].position.x = 200;
	v[1].position.y = 450;
	v[1].color = {0, 0, 255, 255};

	v[2].position.x = 600;
	v[2].position.y = 450;
	v[2].color = {0, 255, 0, 255};
				
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
	while(true)
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
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderGeometry(renderer, nullptr, v, 3, nullptr, 0);

        SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);

		win->Present();

	}

    return 0;
}
