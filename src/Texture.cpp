#include "Texture.h"
#include "Window.h"
#include "ConLog.h"


using namespace PaceLib;


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
