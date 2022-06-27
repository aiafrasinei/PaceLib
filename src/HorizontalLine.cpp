#include "HorizontalLine.h"
#include "Window.h"

using namespace PaceLib;


HorizontalLine::HorizontalLine(std::string name, float x1, float y1, float size, SDL_Color color)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x1 + size;
    this->y2 = y1;

    hidden = false;

    SetColor(color.r, color.g, color.b, color.a);

    this->name = name;
}

HorizontalLine::~HorizontalLine()
{

}

void HorizontalLine::Create(std::string name, Shape *parent, float x1, float y1, float size, SDL_Color color)
{
    parent->Add(new HorizontalLine(name, x1, y1, size, color));
}

void HorizontalLine::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(Window::GetRenderer(), x1, y1, x2, y2);
    }
}
