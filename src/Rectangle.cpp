#include "Rectangle.h"
#include "Window.h"

using namespace PaceLib;

Rectangle::Rectangle(std::string name, Shape *parent, SDL_Rect shape, SDL_Color color)
{
    SetColor(color.r, color.g, color.b, color.a);

    rect.x = shape.x;
    rect.y = shape.y;
    rect.w = shape.w;
    rect.h = shape.h;

    hidden = false;
    rounded = false;
    
    rtype = DrawTypes::OUTLINE;

    this->name = name;
}

Rectangle::~Rectangle()
{

}

void Rectangle::Create(std::string name, Shape *parent, SDL_Rect shape, SDL_Color color)
{
    parent->Add(new Rectangle(name, parent, shape, color));
}

void Rectangle::CreateSquare(std::string name, Shape *parent, int x, int y, int size, SDL_Color color)
{
    SDL_Rect shape = {x , y, size , size};
    parent->Add(new Rectangle(name, parent, shape, color));
}

void Rectangle::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

        if(rtype == DrawTypes::OUTLINE) {
            SDL_RenderDrawRect(Window::GetRenderer(), &rect);
        } else if(rtype == DrawTypes::FILLED) {
            SDL_RenderFillRect(Window::GetRenderer(), &rect);
        }
    }
}

void Rectangle::SetRect(float x, float y, float w , float h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Rectangle::SetRounded(bool rounded)
{
    this->rounded = rounded;
}