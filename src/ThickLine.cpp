#include "ThickLine.h"
#include "Window.h"

using namespace PaceLib;

ThickLine::ThickLine(WidgetId wid, int x1, int y1, int x2, int y2, int size, SDL_Color color)
{
    //TODO

    SetColor(color.r, color.g, color.b, color.a);

    this->name = wid.name;
}

ThickLine::~ThickLine()
{

}

void ThickLine::Create(WidgetId wid)
{
     if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int x2 = conf->Get("x2");
        int y2 = conf->Get("y2");
        int size = conf->Get("size");
        
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        wid.parent->Add(new ThickLine(wid, x1, y1, x2, y2, size, color));
    }
}

void ThickLine::Create(WidgetId wid, int x1, int y1, int x2, int y2, int size, SDL_Color color)
{
    wid.parent->Add(new ThickLine(wid, x1, y1, x2, y2, size, color));
}

void ThickLine::Draw()
{
    if(!hidden) {
        for(int i=0; i<15; i++) {
            verts[i].color = {color.r, color.g, color.b, color.a};
        }

        SDL_RenderGeometry(Window::GetRenderer(), NULL, verts, 15, NULL, 0);
    }
}
