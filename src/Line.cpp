#include "Line.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Line::Line(ShapeId wid, int x1, int y1, int x2, int y2, SDL_Color color)
{
    if(wid.name == "root") {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    } else {
        this->x1 = static_cast<Widget *>(wid.parent)->GetRect().x + x1;
        this->y1 = static_cast<Widget *>(wid.parent)->GetRect().y + y1;
        this->x2 = static_cast<Widget *>(wid.parent)->GetRect().x + x2;
        this->y2 = static_cast<Widget *>(wid.parent)->GetRect().y + y2;
    }

    hidden = false;

    this->name = name;

    SetColor(color.r, color.g, color.b, color.a);

    rtype = DrawTypes::OUTLINE;
}

Line::~Line()
{

}

void Line::Create(ShapeId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int x2 = conf->Get("x2");
        int y2 = conf->Get("y2");

        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};
        wid.parent->Add(new Line(wid, x1, y1, x2, y2, color));
    }
}

void Line::Create(std::string name)
{
    Line::Create({&Root::GetInstance(), name});
}

void Line::Create(ShapeId wid, int x1, int y1, int x2, int y2, SDL_Color color)
{
    wid.parent->Add(new Line(wid, x1, y1, x2, y2, color));
}

void Line::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(Window::GetRenderer(), x1, y1, x2, y2);
    }
}

