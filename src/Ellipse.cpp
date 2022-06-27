#include "Ellipse.h"
#include "Window.h"

using namespace PaceLib;

Ellipse::Ellipse(std::string name, float x, float y, float rx, float ry, SDL_Color color)
{
    this->x = x;
    this->y = y;
    this->rx = rx;
    this->ry = ry;

    hidden = false;

    rtype = DrawTypes::OUTLINE;

    SetColor(color.r, color.g, color.b, color.a);
    this->name = name;
}

Ellipse::~Ellipse()
{

}

void Ellipse::Create(std::string name, Shape *parent, float x, float y, float rx, float ry, SDL_Color color)
{
    parent->Add(new Ellipse(name, x, y, rx, ry, color));
}

void Ellipse::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        //TODO
    }
}

void Ellipse::SetDrawType(DrawTypes rtype)
{
    this->rtype = rtype;
}
