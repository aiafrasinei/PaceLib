#include "CheckBox.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

CheckBox::CheckBox(ShapeId sid, PropDimColor dco, PropFontText fto, SDL_Color textColor)
{
    if(sid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dco.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dco.rect.y;
    }

    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;

    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    this->textColor = textColor;

    if(sid.parent->name == "root") {
        Text::Begin({sid.parent, sid.name + "_text"}, fto, rect.x + rect.w/50, rect.y, textColor);
    } else {
        Text::Begin({sid.parent, sid.name + "_text"}, fto, rect.x + rect.w*1.5, rect.y - rect.h/3.1, textColor);
    }

    this->name = sid.name;

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

CheckBox::CheckBox(ShapeId sid, PropTex pto)
{
    if(sid.parent->name == "root") {
        rect.x = pto.rect.x;
        rect.y = pto.rect.y;
    } else {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + pto.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + pto.rect.y;
    }
    rect.w = pto.rect.w;
    rect.h = pto.rect.h;

    hidden = false;

    this->tex = pto.tex;

    this->name = sid.name;

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

void CheckBox::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

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

        fto.font = Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
        fto.text = conf->Get("text").get<std::string>();

        SDL_Color textColor = {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]};

        CheckBox *newc = new CheckBox(sid, dco, fto, textColor);

        newc->SetTextColor({conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});
        newc->conf = conf;

        sid.parent->Add(newc);

        newc->InternalInit();
    }
}


void CheckBox::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    CheckBox::Begin({root->GetCurrent(), name});
}

void CheckBox::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    CheckBox::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void CheckBox::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void CheckBox::Begin(ShapeId sid, PropDimColor dco, PropFontText fto, SDL_Color textColor)
{
    CheckBox *newc = new CheckBox(sid, dco, fto, textColor);
    newc->InternalInit();

    sid.parent->Add(newc); 
}

void CheckBox::Begin(ShapeId sid, PropTex pto)
{
    sid.parent->Add(new CheckBox(sid, pto));
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

    //to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
}

void CheckBox::InternalInit()
{
    //child text
    Root *root = &Root::GetInstance();
    CheckBox *newc = (CheckBox *)root->GetCurrent()->Get(name);

    Text::Begin( {newc, newc->name+"_text"}, fto, newc->GetRect().x + newc->GetRect().w*1.5, newc->GetRect().y - newc->GetRect().h/3.1, {0,0,0,255});

    Text *to = (Text *)newc->Get(name + "_text");
    to->SetTextColor(newc->GetTextColor());
}

SDL_Color CheckBox::GetTextColor()
{
    return textColor;
}