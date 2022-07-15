#include "VerticalLine.h"
#include "Window.h"

using namespace PaceLib;


VerticalLine::VerticalLine(WidgetId wid, float x1, float y1, float size, SDL_Color color)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x1;
    this->y2 = y1 + size;

    hidden = false;

    SetColor(color.r, color.g, color.b, color.a);

    this->name = wid.name;
}

VerticalLine::~VerticalLine()
{

}

void VerticalLine::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int size = conf->Get("size");

        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};
        wid.parent->Add(new VerticalLine(wid, x1, y1, size, color));
    }
}

void VerticalLine::Create(WidgetId wid, float x1, float y1, float size, SDL_Color color)
{
    wid.parent->Add(new VerticalLine(wid, x1, y1, size, color));
}

void VerticalLine::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(Window::GetRenderer(), x1, y1, x2, y2);
    }
}
