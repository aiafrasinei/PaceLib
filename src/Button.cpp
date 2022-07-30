#include "Button.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;


Button::Button(ShapeId wid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID})
{
    if(wid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = static_cast<Widget *>(wid.parent)->GetRect().x + dco.rect.x;
        rect.y = static_cast<Widget *>(wid.parent)->GetRect().y + dco.rect.y;
    }

    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;

    this->align = align;
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    if(wid.parent->name == "root") {
        to = Text::Create(fto.font, fto.text, rect.x + rect.w/50, rect.y, textColor);
    } else {
        to = Text::Create(fto.font, fto.text, rect.x + rect.w/10, rect.y, textColor);
    }
    InternalAlign(align);

    this->name = wid.name;

    mouseOver = false;

    highlight = true;

    Uint8 hr = color.r + 30;
    Uint8 hg = color.g + 30;
    Uint8 hb = color.b + 30;
    Uint8 ha = 255;
    highlightColor = { hr , hg , hb, ha };

    tex = nullptr;

    wtype = WidgetType::BUTTON;
    
    onClickCallback = nullptr;
}

Button::~Button()
{

}

//load all info from conf file ( {dim, color}, {font_name, text}, align )
void Button::Create(ShapeId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        Align align;
        if(conf->Get("align")[0] == "mid") {
            align.valign = V::MID;
        } else if(conf->Get("align")[0] == "top") {
            align.valign = V::TOP;
        } else if(conf->Get("align")[0] == "bottom") {
            align.valign = V::BOTTOM;
        }

        if(conf->Get("align")[1] == "left") {
            align.halign = H::LEFT;
        } else if(conf->Get("align")[1] == "mid") {
            align.halign = H::MID;
        } else if(conf->Get("align")[1] == "right") {
            align.halign = H::RIGHT;
        }

        Button *lb = new Button( wid, 
            {{dim[0], dim[1], dim[2], dim[3]},
            {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}},
            {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
            align);

        lb->SetTextColor({conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});

        lb->conf = conf;
        wid.parent->Add(lb);
    }
}

void Button::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    Button::Create({(Widget *)root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->Get(root->GetCurrent()->name)->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }
}

void Button::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Button::Create(ShapeId wid, PropDimColor dco, PropFontText fto, Align align)
{
    wid.parent->Add(new Button(wid, dco, fto, align)); 
}

void Button::Create(ShapeId wid, SDL_Rect dim, std::string text, Align align)
{
    wid.parent->Add(new Button( wid, {dim, {120, 120, 120, 255}}, {Root::GetInstance().GetScene("Default").GetFont("default"), text}, align));
}

void Button::Create(ShapeId wid, SDL_Rect dim)
{
    wid.parent->Add(new Button(wid, { dim, {120, 120, 120, 255} }, {Root::GetInstance().GetScene("Default").GetFont("default"), ""}));
}

void Button::InternalAlign(Align align)
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

void Button::SetTextAlign(Align align)
{
    this->align = align;
}

void Button::SetTextColor(SDL_Color color)
{
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;

    to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
}

void Button::Draw()
{
    if(!hidden) {
        if(mouseOver) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
        } else {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        }

        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 90, 90, 90, 255);
        SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);
     

        for(Shape *w : shapes) {
            w->Draw();
        }

        //SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
        if(tex == nullptr) {
            to->Draw();
        }
    }
}

void Button::Update(SDL_Event *e)
{
    if(!hidden) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        static int nr = 0;
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

void Button::SetHighlight(bool state)
{
    highlight = state;
}

void Button::SetHighlightColor(SDL_Color color)
{
    highlightColor.r = color.r;
    highlightColor.g = color.g;
    highlightColor.b = color.b;
    highlightColor.a = color.a;
}

int Button::GetTextSize()
{
    return to->GetWidth();
}

std::string Button::GetText()
{
    return name;
}