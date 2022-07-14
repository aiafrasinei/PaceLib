#include "Hotspot.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

Hotspot::Hotspot(WidgetId wid, PropDimColor dco, Hover type, SDL_Texture *tex)
{
    if(wid.parent->name == "root") {
        this->rect.x = dco.rect.x;
        this->rect.y = dco.rect.y;
    } else {
        this->rect.x = wid.parent->GetRect().x + dco.rect.x;
        this->rect.y = wid.parent->GetRect().y + dco.rect.y;
    }
    
    this->rect.w = dco.rect.w;
    this->rect.h = dco.rect.h;

    hidden = false;

    this->name = wid.name;

    mouseOver = false;

    isHighlight = true;

    this->highlight = dco.color;

    this->type = type;

    this->tex = tex;

    wtype = WidgetType::HOTSPOT;

    onClickCallback = nullptr;
}

Hotspot::~Hotspot()
{

}

void Hotspot::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        wid.parent->Add(new Hotspot(wid, { {dim[0], dim[1], dim[2], dim[3]}, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]} }));
    }
}

void Hotspot::Create(WidgetId wid, PropDimColor dco, Hover type, SDL_Texture *tex)
{
    wid.parent->Add(new Hotspot(wid, dco, type, tex));
}


void Hotspot::SetRec(SDL_Rect rect)
{
    this->rect = rect;
}

void Hotspot::Draw()
{
    if(!hidden) {
        if(mouseOver) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), highlight.r, highlight.g, highlight.b, highlight.a);
            if(type == Hover::FILLED) {
                SDL_RenderFillRect(Window::GetRenderer(), &rect);
            } else if (type == Hover::RECT) {
                SDL_RenderDrawRect(Window::GetRenderer(), &rect);
            } else if (type == Hover::TEXTURE) {
                if(tex != nullptr) {
                    SDL_RenderCopy(Window::GetRenderer(), tex, NULL, &rect);
                }
            }
        }

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void Hotspot::Update(SDL_Event *e)
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

        if(isHighlight) {
            if(PointInRect({x, y}, rect)) {
                mouseOver = true;
            } else {
                mouseOver = false;
            }
            
        }
    }
}

void Hotspot::SetHighlight(bool state)
{
    isHighlight = state;
}

void Hotspot::SetHighlightColor(SDL_Color color)
{
    highlight.r = color.r;
    highlight.g = color.g;
    highlight.b = color.b;
    highlight.a = color.a;
}
