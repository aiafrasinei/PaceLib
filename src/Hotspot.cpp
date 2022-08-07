#include "Hotspot.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

Hotspot::Hotspot(ShapeId sid, PropDimColor dco, Hover type, SDL_Texture *tex)
{
    if(sid.parent->name == "root") {
        this->rect.x = dco.rect.x;
        this->rect.y = dco.rect.y;
    } else {
        this->rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dco.rect.x;
        this->rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dco.rect.y;
    }
    
    this->rect.w = dco.rect.w;
    this->rect.h = dco.rect.h;

    hidden = false;

    this->name = sid.name;

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

void Hotspot::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        sid.parent->Add(new Hotspot(sid, { {dim[0], dim[1], dim[2], dim[3]}, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]} }));
    }
}

void Hotspot::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    Hotspot::Begin({root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->GetCurrent()->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }
}

void Hotspot::Begin(ShapeId sid, PropDimColor dco, Hover type, SDL_Texture *tex)
{
    sid.parent->Add(new Hotspot(sid, dco, type, tex));
}

void Hotspot::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
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
