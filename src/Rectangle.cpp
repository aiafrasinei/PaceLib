#include "Rectangle.h"
#include "Window.hpp"
#include "Root.h"

using namespace PaceLib;

Rectangle::Rectangle(ShapeId sid, SDL_Rect dim, SDL_Color color)
{
    SetColor(color);

    if(sid.parent->name == "root") {
        rect.x = dim.x;
        rect.y = dim.y;
    } else {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dim.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dim.y;
    }

    rect.w = dim.w;
    rect.h = dim.h;

    hidden = false;
    rounded = false;
    
    rtype = DrawTypes::OUTLINE;

    this->name = sid.name;
}

Rectangle::~Rectangle()
{

}

void Rectangle::Begin(ShapeId sid)
{
     if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        sid.parent->Add(new Rectangle(sid, {dim[0], dim[1], dim[2], dim[3]}, color));
    }
}

void Rectangle::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Rectangle::Begin({root->GetCurrent(), name});
}

void Rectangle::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Rectangle::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Rectangle::Begin(ShapeId sid, SDL_Rect shape, SDL_Color color)
{
    sid.parent->Add(new Rectangle(sid, shape, color));
}

void Rectangle::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
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