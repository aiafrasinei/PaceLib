#include "Sprite.h"
#include "Window.h"

using namespace PaceLib;

Sprite::Sprite(std::string name, SDL_Texture *tex, SDL_Rect shape)
{
    this->tex = tex;
    rect.x = shape.x;
    rect.y = shape.y;
    rect.w = shape.w;
    rect.h = shape.h;

    hidden = false;
    
    this->name = name;
}

Sprite::~Sprite()
{

}

void Sprite::Create(std::string name, Shape *parent, SDL_Texture *tex, SDL_Rect shape)
{
    parent->Add(new Sprite(name, tex, shape));
}

void Sprite::Draw()
{
    if(!hidden) {
        SDL_RenderCopy(Window::GetRenderer(), tex, NULL, &rect);
    }
}

void Sprite::SetTex(SDL_Texture *tex)
{
    this->tex = tex;
}

void Sprite::SetRect(float x, float y, float w , float h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}
