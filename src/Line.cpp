#include "Line.h"
#include "Window.h"

using namespace PaceLib;

Line::Line(std::string name, float x1, float y1, float x2, float y2, SDL_Color color)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;

    hidden = false;

    this->name = name;

    SetColor(color.r, color.g, color.b, color.a);

    rtype = DrawTypes::OUTLINE;
}

Line::~Line()
{

}

void Line::Create(std::string name, Shape *parent, float x1, float y1, float x2, float y2, SDL_Color color)
{
    parent->Add(new Line(name, x1, y1, x2, y2, color));
}

void Line::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(Window::GetRenderer(), x1, y1, x2, y2);
    }
}

