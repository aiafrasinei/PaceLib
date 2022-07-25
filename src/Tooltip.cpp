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

void Tooltip::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        SDL_Rect child = wid.parent->GetRect();
        
        wid.parent->Add(new Tooltip( wid , child, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}));
    }
}

void Tooltip::Create(std::string name)
{
    Tooltip::Create({&Root::GetInstance(), name});
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

DefaultTooltip::DefaultTooltip(WidgetId wid, PropFontText fto, SDL_Color color, SDL_Color textColor)
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

    to = Text::Create(fto.font, fto.text, rect.x, rect.y, textColor);
    to->SetX(this->GetHalfX() - to->GetWidth()/2);
}

void DefaultTooltip:: Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        if(conf->Get("color") == "parent") {
            wid.parent->Add(new DefaultTooltip(wid, {Root::GetInstance().GetScene("Default").GetFont("default"), conf->Get("text").get<std::string>() }, wid.parent->GetColor(), {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]}));
        } else {
            wid.parent->Add(new DefaultTooltip(wid, {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()} , {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}, {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]}));
        }
    }
}

void DefaultTooltip:: Create(WidgetId wid, PropFontText fto, SDL_Color color, SDL_Color text_color)
{
    wid.parent->Add(new DefaultTooltip(wid, fto, color, {0, 0, 0, 255}));
}

void DefaultTooltip::Create(WidgetId wid, std::string text)
{
    wid.parent->Add(new DefaultTooltip(wid, {Root::GetInstance().GetScene("Default").GetFont("default"), text }, wid.parent->GetColor(), {0, 0, 0, 255}));
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

void DefaultTooltip::SetTextColor(SDL_Color color)
{
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;

    to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
}