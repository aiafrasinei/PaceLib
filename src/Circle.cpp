#include "Circle.h"
#include "Window.h"

using namespace PaceLib;


Circle::Circle(std::string name, float x, float y, float radius, SDL_Color color)
{
    this->x = x;
    this->y = y;
    this->radius = radius;

    hidden = false;

    rtype = DrawTypes::OUTLINE;

    SetColor(color.r, color.g, color.b, color.a);

    this->name = name;
}

Circle::~Circle()
{

}

void Circle::Create(std::string name, Shape *parent, float x, float y, float radius, SDL_Color color)
{
    parent->Add(new Circle(name, x, y, radius, color));
}

void Circle::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        
        if(rtype == DrawTypes::OUTLINE) {
            int offsetx, offsety, d;
            int status;
            
            offsetx = 0;
            offsety = radius;
            d = radius -1;
            status = 0;

            while (offsety >= offsetx) {
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x + offsetx, y + offsety);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x + offsety, y + offsetx);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x - offsetx, y + offsety);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x - offsety, y + offsetx);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x + offsetx, y - offsety);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x + offsety, y - offsetx);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x - offsetx, y - offsety);
                status += SDL_RenderDrawPoint(Window::GetRenderer(), x - offsety, y - offsetx);

                if (status < 0) {
                    status = -1;
                    break;
                }

                if (d >= 2*offsetx) {
                    d -= 2*offsetx + 1;
                    offsetx +=1;
                }
                else if (d < 2 * (radius - offsety)) {
                    d += 2 * offsety - 1;
                    offsety -= 1;
                }
                else {
                    d += 2 * (offsety - offsetx - 1);
                    offsety -= 1;
                    offsetx += 1;
                }
            }
        } else if (rtype == DrawTypes::FILLED) {
            int offsetx, offsety, d;
            int status;

            offsetx = 0;
            offsety = radius;
            d = radius -1;
            status = 0;

            while (offsety >= offsetx) {

                status += SDL_RenderDrawLine(Window::GetRenderer(), x - offsety, y + offsetx, x + offsety, y + offsetx);
                status += SDL_RenderDrawLine(Window::GetRenderer(), x - offsetx, y + offsety, x + offsetx, y + offsety);
                status += SDL_RenderDrawLine(Window::GetRenderer(), x - offsetx, y - offsety, x + offsetx, y - offsety);
                status += SDL_RenderDrawLine(Window::GetRenderer(), x - offsety, y - offsetx, x + offsety, y - offsetx);

                if (status < 0) {
                    status = -1;
                    break;
                }

                if (d >= 2*offsetx) {
                    d -= 2*offsetx + 1;
                    offsetx +=1;
                }
                else if (d < 2 * (radius - offsety)) {
                    d += 2 * offsety - 1;
                    offsety -= 1;
                }
                else {
                    d += 2 * (offsety - offsetx - 1);
                    offsety -= 1;
                    offsetx += 1;
                }
            }
        }
    }
}

