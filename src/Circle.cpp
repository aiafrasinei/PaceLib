#include "Circle.h"
#include "Window.h"

using namespace PaceLib;


Circle::Circle(WidgetId wid, float x, float y, float radius, SDL_Color color)
{
    if(wid.parent->name == "root") {
        this->x = x;
        this->y = y;
    } else {
        this->x = wid.parent->GetRect().x + x;
        this->y = wid.parent->GetRect().y + y;
    }

    this->radius = radius;

    hidden = false;

    rtype = DrawTypes::OUTLINE;

    SetColor(color.r, color.g, color.b, color.a);

    this->name = wid.name;
}

Circle::~Circle()
{

}

void Circle::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int x = conf->Get("x");
        int y = conf->Get("y");
        int radius = conf->Get("radius");
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        wid.parent->Add(new Circle(wid, x, y, radius, color));
    }
}

void Circle::Create(WidgetId wid, float x, float y, float radius, SDL_Color color)
{
    wid.parent->Add(new Circle(wid, x, y, radius, color));
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

