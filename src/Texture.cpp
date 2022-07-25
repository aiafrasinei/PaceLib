#include "Texture.h"
#include "Window.h"
#include "ConLog.h"
#include "Root.h"


using namespace PaceLib;

Tex::Tex(std::string path, int x, int y)
{
    tex = NULL;

	rect.x = x;
	rect.y = y;

	Free();

	SDL_Texture* newtex = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if( loadedSurface == NULL )
	{
		ConLog::Error("Unable to load image " + path + " Error: " + IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newtex = SDL_CreateTextureFromSurface(Window::GetRenderer(), loadedSurface);
		if(newtex == NULL)
		{
			ConLog::Error("Unable to create texture from " + path + " Error " + SDL_GetError());
		}
		else
		{
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	tex = newtex;
}

Tex::Tex(std::string path, int x, int y, int w, int h)
{
    tex = NULL;

	rect.x = x;
	rect.y = y;

	Free();

	SDL_Texture* newtex = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if( loadedSurface == NULL )
	{
		ConLog::Error("Unable to load image " + path + " Error: " + IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newtex = SDL_CreateTextureFromSurface(Window::GetRenderer(), loadedSurface);
		if(newtex == NULL)
		{
			ConLog::Error("Unable to create texture from " + path + " Error " + SDL_GetError());
		}
		else
		{
			rect.w = w;
			rect.h = h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	tex = newtex;
}

Tex::Tex(SDL_Texture *tex, int x, int y, int w, int h)
{
    this->tex = tex;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

Tex::Tex(SDL_Texture *tex, int x, int y)
{
    this->tex = tex;

	int wl, hl;
	SDL_QueryTexture(this->tex, NULL, NULL, &wl, &hl);

	rect.x = x;
	rect.y = y;
	rect.w = wl;
	rect.h = hl;
}

Tex::~Tex()
{
    Free();
}

void Tex::Free()
{
	if(tex != NULL)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
	}
}

void Tex::Draw(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if(!hidden) {
		SDL_Rect renderQuad = { x, y, rect.w, rect.h };

		if( clip != NULL )
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopyEx(Window::GetRenderer(), tex, clip, &renderQuad, angle, center, flip);
	}
}

void Tex::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(tex, r, g, b);
}

void Tex::SetBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode(tex, blending);
}
		
void Tex::SetAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(tex, a);
}


Texture::Texture(WidgetId wid, SDL_Texture *tex, SDL_Rect dim)
{
	if(wid.parent->name == "root") {
        rect.x = dim.x;
        rect.y = dim.y;
    } else {
        rect.x = wid.parent->GetRect().x + dim.x;
        rect.y = wid.parent->GetRect().y + dim.y;
    }
    
    rect.w = dim.w;
    rect.h = dim.h;

    hidden = false;

    this->tex = tex;

	this->name = wid.name;

	ctex = new Tex(tex, 0, 0, dim.w, dim.h);

    wtype = WidgetType::TEXTURE;
}

Texture::~Texture()
{
    if(tex != NULL)
	{
		delete ctex;
		tex = NULL;
	}
}

void Texture::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        SDL_Texture *tex = Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetTex(conf->Get("tex_name").get<std::string>());
        wid.parent->Add(new Texture(wid, tex, {dim[0], dim[1], dim[2], dim[3]}));
    }
}

void Texture::Create(std::string name)
{
    Texture::Create({&Root::GetInstance(), name});
}

void Texture::Create(WidgetId wid, SDL_Texture *tex, int x, int y)
{
	int wl, hl;
	SDL_QueryTexture(tex, NULL, NULL, &wl, &hl);

	wid.parent->Add(new Texture(wid, tex, {x, y, wl, hl}));
}

void Texture::Create(WidgetId wid, SDL_Texture *tex, SDL_Rect dim)
{
	wid.parent->Add(new Texture(wid, tex, dim));
}

void Texture::Draw()
{
	if(!hidden) {
		ctex->Draw(rect.x,rect.y);

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(tex, r, g, b);
}

void Texture::SetBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode(tex, blending);
}
		
void Texture::SetAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(tex, a);
}
