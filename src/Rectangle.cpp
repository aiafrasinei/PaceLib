#include "Rectangle.h"
#include "Window.h"

using namespace PaceLib;

Rectangle::Rectangle(WidgetId wid, SDL_Rect dim, SDL_Color color)
{
    SetColor(color.r, color.g, color.b, color.a);

    if(wid.parent->name == "root") {
        rect.x = dim.x;
        rect.y = dim.y;
    } else {
        rect.x = wid.parent->GetRect().x + dim.x;
        rect.y = wid.parent->GetRect().y + dim.y;
    }

    rect.w = dim.w;
    rect.h = dim.h;

    hidden = false;
    rounded = false;
    
    rtype = DrawTypes::OUTLINE;

    this->name = wid.name;
}

Rectangle::~Rectangle()
{

}

void Rectangle::Create(WidgetId wid)
{
     if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        wid.parent->Add(new Rectangle(wid, {dim[0], dim[1], dim[2], dim[3]}, color));
    }
}

void Rectangle::Create(WidgetId wid, SDL_Rect shape, SDL_Color color)
{
    wid.parent->Add(new Rectangle(wid, shape, color));
}

void Rectangle::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

        if(rtype == DrawTypes::OUTLINE) {
            SDL_RenderDrawRect(Window::GetRenderer(), &rect);
        } else if(rtype == DrawTypes::FILLED) {
            SDL_RenderFillRect(Window::GetRenderer(), &rect);
        }
    }
}

void Rectangle::SetRect(float x, float y, float w , float h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Rectangle::SetRounded(bool rounded)
{
    this->rounded = rounded;
}