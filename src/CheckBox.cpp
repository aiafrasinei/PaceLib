#include "CheckBox.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

CheckBox::CheckBox(WidgetId wid, PropDimColor dco, PropFontText fto, SDL_Color textColor)
{
    if(wid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y ;
    } else {
        rect.x = wid.parent->GetRect().x + dco.rect.x;
        rect.y = wid.parent->GetRect().y + dco.rect.y;
    }

    if(wid.parent->name == "root") {
        rect.w = dco.rect.w + rect.w/50;
    } else {
        rect.w = dco.rect.w + rect.w/10;
    }
    rect.h = dco.rect.h;

    hidden = false;

    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    this->textColor = textColor;

    if(wid.parent->name == "root") {
        to = Text::Create(fto.font, fto.text, rect.x + rect.w/50, rect.y, textColor);
    } else {
        to = Text::Create(fto.font, fto.text, rect.x + rect.w*1.5, rect.y - rect.h/3.1, textColor);
    }

    this->name = wid.name;

    mouseOver = false;

    highlight = true;

    Uint8 hr = color.r + 30;
    Uint8 hg = color.g + 30;
    Uint8 hb = color.b + 30;
    Uint8 ha = 255;
    highlightColor = { hr , hg , hb, ha };

    tex = nullptr;

    checked = false;

    wtype = WidgetType::CHECKBOX;

    onClickCallback = [this]() {
        if(checked) {
            checked = false;
        } else {
            checked = true;
        }
    };

    midrect = { rect.x+rect.w/4, rect.y+rect.h/4, rect.w/2, rect.h/2 };
}

CheckBox::CheckBox(WidgetId wid, PropTex pto)
{
    if(wid.parent->name == "root") {
        rect.x = pto.rect.x;
        rect.y = pto.rect.y;
    } else {
        rect.x = wid.parent->GetRect().x + pto.rect.x;
        rect.y = wid.parent->GetRect().y + pto.rect.y;
    }
    rect.w = pto.rect.w;
    rect.h = pto.rect.h;

    hidden = false;

    this->tex = pto.tex;

    this->name = wid.name;

    mouseOver = false;

    highlight = true;

    Uint8 hr = color.r + 30;
    Uint8 hg = color.g + 30;
    Uint8 hb = color.b + 30;
    Uint8 ha = 255;
    highlightColor = { hr , hg , hb, ha };

    checked = false;

    onClickCallback = [this]() {
        if(checked) {
            checked = false;
        } else {
            checked = true;
        }
    };

    wtype = WidgetType::CHECKBOX;
}

CheckBox::~CheckBox()
{

}

void CheckBox::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropDimColor dco;

        dco.rect.x = dim[0];
        dco.rect.y = dim[1];
        dco.rect.w = dim[2];
        dco.rect.h = dim[3];

        dco.color.r = conf->Get("color")[0];
        dco.color.g = conf->Get("color")[1];
        dco.color.b = conf->Get("color")[2];
        dco.color.a = conf->Get("color")[3];

        PropFontText fto;

        fto.font = Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>());
        fto.text = conf->Get("text").get<std::string>();

        SDL_Color textColor = {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]};

        wid.parent->Add(new CheckBox(wid, dco, fto, textColor));
    }
}

void CheckBox::Create(WidgetId wid, PropDimColor dco, PropFontText fto, SDL_Color textColor)
{
    wid.parent->Add(new CheckBox(wid, dco, fto, textColor));
}

void CheckBox::Create(WidgetId wid, PropDimColor dco, std::string text)
{
    wid.parent->Add(new CheckBox(wid, dco, {Root::GetInstance().GetScene("Default").GetFont("default"), text}, {0, 0, 0, 255}));
}

void CheckBox::Create(WidgetId wid, PropTex pto)
{
    wid.parent->Add(new CheckBox(wid, pto));
}

void CheckBox::Draw()
{
    if(!hidden) {
        if(mouseOver) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
        } else {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        }

        if(tex == nullptr) {
            SDL_RenderFillRect(Window::GetRenderer(), &rect);

            SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);
            SDL_RenderDrawRect(Window::GetRenderer(), &rect);

            if(checked) {
                SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);
                SDL_RenderFillRect(Window::GetRenderer(), &midrect);
            }

            SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);
            
        } else {
            SDL_RenderCopy(Window::GetRenderer(), tex, NULL, &rect);
        }

        for(Shape *w : shapes) {
            w->Draw();
        }

        SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
        if(tex == nullptr) {
            to->Draw();
        }

    }
}

void CheckBox::Update(SDL_Event *e)
{
    if(!hidden) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(e->type == SDL_MOUSEBUTTONUP)
        {
            if(PointInRect({x, y}, rect)) {
                if(onClickCallback != nullptr) {
                    onClickCallback();
                    SDL_PollEvent(e);
                }
            }
        }

        if(highlight) {
            if(PointInRect({x, y}, rect)) {
                mouseOver = true;
            } else {
                mouseOver = false;
            }
            
        }
    }
}

void CheckBox::SetHighlight(bool state)
{
    highlight = state;
}

void CheckBox::SetHighlightColor(SDL_Color color)
{
    highlightColor.r = color.r;
    highlightColor.g = color.g;
    highlightColor.b = color.b;
    highlightColor.a = color.a;
}

bool CheckBox::IsChecked()
{
    return checked;
}

void CheckBox::SetTextColor(SDL_Color color)
{
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;

    to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
}