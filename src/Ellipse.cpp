#include "Ellipse.h"
#include "Window.h"


using namespace PaceLib;

Ellipse::Ellipse(WidgetId wid, float x, float y, float rx, float ry, SDL_Color color)
{
    if(wid.parent->name == "root") {
        this->x = x;
        this->y = y;
        this->rx = rx;
        this->ry = ry;
    } else {
        this->x = wid.parent->GetRect().x + x;
        this->y = wid.parent->GetRect().y + y;
        this->rx = wid.parent->GetRect().x + rx;
        this->ry = wid.parent->GetRect().y + ry;
    }

    hidden = false;

    rtype = DrawTypes::OUTLINE;

    SetColor(color.r, color.g, color.b, color.a);
    this->name = wid.name;
}

Ellipse::~Ellipse()
{

}

void Ellipse::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int x = conf->Get("x");
        int y = conf->Get("y");
        int rx = conf->Get("rx");
        int ry = conf->Get("ry");
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        wid.parent->Add(new Ellipse(wid, x, y, rx, ry, color));
    }
}

void Ellipse::Create(WidgetId wid, float x, float y, float rx, float ry, SDL_Color color)
{
    wid.parent->Add(new Ellipse(wid, x, y, rx, ry, color));
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
