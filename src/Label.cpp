#include "Label.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

Label::Label(WidgetId wid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID})
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

    this->align = align;
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    to = Text::Create(fto.font, fto.text, rect.x, rect.y, textColor);
    InternalAlign(align);

    this->name = wid.name;

    wtype = WidgetType::LABEL;
}

Label::~Label()
{

}

void Label::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        Label *lb = nullptr;
        if (conf->Get("color") == "parent") {
            lb = new Label( wid, 
                {{dim[0], dim[1], dim[2], dim[3]},
                {wid.parent->GetColor().r, wid.parent->GetColor().g, wid.parent->GetColor().b, wid.parent->GetColor().a}},
                {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
                {V::MID, H::MID});

        } else {
            lb = new Label( wid, 
                {{dim[0], dim[1], dim[2], dim[3]},
                {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}},
                {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
                {V::MID, H::MID});
        }

        lb->SetTextColor({conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});

        lb->conf = conf;
        wid.parent->Add(lb);
    }
}

void Label::Create(WidgetId wid, PropDimColor dco, PropFontText fto, Align align)
{
    wid.parent->Add(new Label( wid, dco, fto, align ));
}

void Label::Create(WidgetId wid, SDL_Rect dim, std::string text)
{
    wid.parent->Add(new Label( wid, {dim, {wid.parent->GetColor().r, wid.parent->GetColor().g, wid.parent->GetColor().b, wid.parent->GetColor().a}}, {Root::GetInstance().GetScene("Default").GetFont("default"), text}));
}

void Label::InternalAlign(Align align)
{
    if(align.valign == V::TOP) {
        if (align.halign == H::MID) {
            to->SetX(this->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(this->rect.x + this->rect.w - to->GetWidth());
        }
    } else if (align.valign == V::MID) {
        if (align.halign == H::MID) {
            to->SetX(this->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(this->rect.x + this->rect.w - to->GetWidth());
        }
        to->SetY(this->GetHalfY() - to->GetHeight()/2);
    } else if (align.valign == V::BOTTOM) {
        if (align.halign == H::MID) {
            to->SetX(this->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(this->rect.x + this->rect.w - to->GetWidth());
        }
        to->SetY(this->rect.y + this->rect.h - to->GetHeight());
    }
}

void Label::SetTextAlign(Align align)
{
    this->align = align;
}

void Label::SetTextColor(SDL_Color color)
{
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;

    to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
}

void Label::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
 
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);

        for(Shape *w : shapes) {
            w->Draw();
        }

        SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
        to->Draw();
    }
}
