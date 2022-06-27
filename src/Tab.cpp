#include "Tab.h"
#include "Window.h"

using namespace PaceLib;

Tab::Tab(WidgetId wid, PropDimColor dco)
{
    if(wid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = wid.parent->GetRect().x + dco.rect.x;
        rect.y = wid.parent->GetRect().y + dco.rect.y;
    }
    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;

    
    this->color.r = dco.color.r;
    this->color.g = dco.color.g;
    this->color.b = dco.color.b;
    this->color.a = dco.color.a;

    this->name = wid.name;
    this->parent = wid.parent;

    wtype = WidgetType::TAB;
}

Tab::~Tab()
{

}

void Tab::Create(WidgetId wid, PropDimColor dco)
{
    wid.parent->Add(new Tab(wid, dco));
}

void Tab::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        for(Shape *w : shapes) {
            w->Draw();
        }

        SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
    }
}

void Tab::Add(Shape *s)
{
    shapes.push_back(s);
}

void Tab::Update(SDL_Event *e)
{
    for(Shape *s : shapes) {
        s->Update(e);
    }
}

Button *Tab::GetButton(std::string child)
{
    return static_cast<Button *>(this->Get(child));
}

ButtonTex *Tab::GetButtonTex(std::string child)
{
    return static_cast<ButtonTex *>(this->Get(child));
}

Label *Tab::GetLabel(std::string child)
{
    return static_cast<Label *>(this->Get(child));
}

Widget *Tab::GetWidget(std::string child)
{
    return static_cast<Widget *>(this->Get(child));
}