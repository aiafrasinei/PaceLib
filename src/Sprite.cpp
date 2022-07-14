#include "Sprite.h"
#include "Window.h"

using namespace PaceLib;

Sprite::Sprite(std::string name, SDL_Texture *tex, SDL_Rect dim, int offset, int nr)
{
    this->tex = tex;
    dest_rect.x = dim.x;
    dest_rect.y = dim.y;
    dest_rect.w = dim.w;
    dest_rect.h = dim.h;

    hidden = false;
    
    this->name = name;

    this->offset = offset;
    this->nr = nr;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = offset;
    src_rect.h = offset;

}

Sprite::~Sprite()
{

}

void Sprite::Create(std::string name, Shape *parent, SDL_Texture *tex, SDL_Rect dim, int offset, int nr)
{
    parent->Add(new Sprite(name, tex, dim, offset, nr));
}

void Sprite::Draw()
{
    if(!hidden) {
        SDL_RenderCopy(Window::GetRenderer(), tex, &src_rect, &dest_rect);
        src_rect.x = src_rect.x + offset;
        if(src_rect.x == nr*offset) {
            src_rect.x = 0;
        }
    }
}

void Sprite::SetTex(SDL_Texture *tex)
{
    this->tex = tex;
}

void Sprite::SetRect(SDL_Rect dim)
{
    dest_rect.x = dim.x;
    dest_rect.y = dim.y;
    dest_rect.w = dim.w;
    dest_rect.h = dim.h;
}
