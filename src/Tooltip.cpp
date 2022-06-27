#include "Tooltip.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Tooltip::Tooltip(WidgetId wid, SDL_Rect shape, SDL_Color color)
{
    this->parent = wid.parent;

    rect.x = shape.x;
    rect.y = shape.y;
    rect.w = shape.w;
    rect.h = shape.h;

    hidden = false;

    
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;

    this->name = wid.name;

    wtype = WidgetType::TOOLTIP;
}

Tooltip::~Tooltip()
{

}

void Tooltip::Create(WidgetId wid, SDL_Color color, Align align)
{
    SDL_Rect child = wid.parent->GetRect();
    if(align.valign == V::BOTTOM && align.halign == H::MID) {
        child.y = child.y + wid.parent->GetRect().h;
    } else if(align.valign == V::BOTTOM && align.halign == H::LEFT) {
        child.x = child.x - wid.parent->GetRect().w;
        child.y = child.y + wid.parent->GetRect().h;
    } else if(align.valign == V::BOTTOM && align.halign == H::RIGHT) {
        child.x = child.x + wid.parent->GetRect().w;
        child.y = child.y + wid.parent->GetRect().h;
    }
    
    if(align.valign == V::TOP && align.halign == H::LEFT) {
        child.x = child.x - wid.parent->GetRect().w;
        child.y = child.y - wid.parent->GetRect().h;
    } else if(align.valign == V::TOP && align.halign == H::RIGHT) {
        child.x = child.x + wid.parent->GetRect().w;
        child.y = child.y - wid.parent->GetRect().h;
    } else if(align.valign == V::TOP && align.halign == H::MID) {
        child.y = child.y - wid.parent->GetRect().h;
    }

    if(align.valign == V::MID && align.halign == H::LEFT) {
        child.x = child.x - wid.parent->GetRect().w;
    } else if(align.valign == V::MID && align.halign == H::RIGHT) {
        child.x = child.x + wid.parent->GetRect().w;
    } else if(align.valign == V::MID && align.halign == H::MID) {
        child.x = child.x + wid.parent->GetRect().w/2;
        child.y = child.y + wid.parent->GetRect().h/2;
    }
    wid.parent->Add(new Tooltip( wid , child, color));
}

void Tooltip::Create(WidgetId wid, int w, int h, SDL_Color color, Align align)
{
     SDL_Rect child = wid.parent->GetRect();

    child.w = w;
    child.h = h;

    if(align.valign == V::BOTTOM && align.halign == H::MID) {
        child.y = child.y + wid.parent->GetRect().h;
    } else if(align.valign == V::BOTTOM && align.halign == H::LEFT) {
        child.x = child.x - wid.parent->GetRect().w;
        child.y = child.y + wid.parent->GetRect().h;
    } else if(align.valign == V::BOTTOM && align.halign == H::RIGHT) {
        child.x = child.x + wid.parent->GetRect().w;
        child.y = child.y + wid.parent->GetRect().h;
    }
    
    if(align.valign == V::TOP && align.halign == H::LEFT) {
        child.x = child.x - wid.parent->GetRect().w;
        child.y = child.y - wid.parent->GetRect().h;
    } else if(align.valign == V::TOP && align.halign == H::RIGHT) {
        child.x = child.x + wid.parent->GetRect().w;
        child.y = child.y - wid.parent->GetRect().h;
    } else if(align.valign == V::TOP && align.halign == H::MID) {
        child.y = child.y - wid.parent->GetRect().h;
    }

    if(align.valign == V::MID && align.halign == H::LEFT) {
        child.x = child.x - wid.parent->GetRect().w;
    } else if(align.valign == V::MID && align.halign == H::RIGHT) {
        child.x = child.x + wid.parent->GetRect().w;
    } else if(align.valign == V::MID && align.halign == H::MID) {
        child.x = child.x + wid.parent->GetRect().w/2;
        child.y = child.y + wid.parent->GetRect().h/2;
    }

    wid.parent->Add(new Tooltip(wid, child, color));
}

void Tooltip::Draw()
{
    if(!hidden) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(PointInRect({x, y}, parent->GetRect())) { 
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

            SDL_RenderFillRect(Window::GetRenderer(), &rect);

            for(Shape *w : shapes) {
                w->Draw();
            }

            SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
        }
    }
}

void Tooltip::Add(Shape *s)
{
    shapes.push_back(s);
}

void Tooltip::Update(SDL_Event *e)
{
    for(Shape *s : shapes) {
        s->Update(e);
    }
}

DefaultTooltip::DefaultTooltip(WidgetId wid, PropFontText fto, SDL_Color color)
{
    this->parent = wid.parent;

    SDL_Rect child = wid.parent->GetRect();

    child.x = child.x + wid.parent->GetRect().w/2;
    child.y = child.y + wid.parent->GetRect().h/2;

    rect.x = child.x;
    rect.y = child.y;
    rect.w = child.w;
    rect.h = child.h;

    hidden = false;

    
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;

    this->name = name;

    to = Text::Create(fto.font, fto.text, rect.x, rect.y, {0, 0, 0, 255});
    to->SetX(this->GetHalfX() - to->GetWidth()/2);
}

void DefaultTooltip:: Create(WidgetId wid, PropFontText fto, SDL_Color color)
{
    wid.parent->Add(new DefaultTooltip(wid, fto, color));
}

void DefaultTooltip::Create(WidgetId wid, std::string text)
{
    wid.parent->Add(new DefaultTooltip(wid, {Root::GetInstance().GetScene("Default").GetFont(0), text }, wid.parent->GetColor()));
}

void DefaultTooltip::Draw()
{
    if(!hidden) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(PointInRect({x, y}, parent->GetRect())) { 
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

            SDL_RenderFillRect(Window::GetRenderer(), &rect);

            for(Shape *w : shapes) {
                w->Draw();
            }

            SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
            
            to->Draw();
        }
    }
}