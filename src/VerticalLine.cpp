#include "VerticalLine.h"
#include "Window.h"

using namespace PaceLib;


VerticalLine::VerticalLine(std::string name, float x1, float y1, float size, SDL_Color color)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x1;
    this->y2 = y1 + size;

    hidden = false;

    SetColor(color.r, color.g, color.b, color.a);

    this->name = name;
}

VerticalLine::~VerticalLine()
{

}

void VerticalLine::Create(std::string name, Shape *parent, float x1, float y1, float size, SDL_Color color)
{
    parent->Add(new VerticalLine(name, x1, y1, size, color));
}

void VerticalLine::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(Window::GetRenderer(), x1, y1, x2, y2);
    }
}
