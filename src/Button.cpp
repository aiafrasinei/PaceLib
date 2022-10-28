#include "Button.h"
#include <functional>
#include "Root.h"
#include "ConLog.hpp"

using namespace PaceLib;

Button::Button(ShapeId sid, ButtonProp prop)
{
    this->prop = prop;

    rect = prop.rect;

    if(sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.rect.y;
    }

    this->prop.rect = rect;

    hidden = false;

    this->name = sid.name;

    mouseOver = false;

    highlight = true;

    wtype = WidgetType::BUTTON;

    onClickCallback = nullptr;

    textSize = 0;
}

Button::~Button()
{
}

// load all info from conf file ( {dim, color}, {font_name, text}, align )
void Button::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Button.conf";
    if (std::filesystem::exists(path))
    {
        Configuration *conf = new Configuration(path);

        int dim[4];
        Widget::ParseDim(dim, conf);

        Align align;
        if (conf->Get("align")[0] == "mid")
        {
            align.valign = V::MID;
        }
        else if (conf->Get("align")[0] == "top")
        {
            align.valign = V::TOP;
        }
        else if (conf->Get("align")[0] == "bottom")
        {
            align.valign = V::BOTTOM;
        }

        if (conf->Get("align")[1] == "left")
        {
            align.halign = H::LEFT;
        }
        else if (conf->Get("align")[1] == "mid")
        {
            align.halign = H::MID;
        }
        else if (conf->Get("align")[1] == "right")
        {
            align.halign = H::RIGHT;
        }

        Root *root = &Root::GetInstance();

        SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
        SDL_Color backgroundColor = ParseVar("background_color", conf, root->GetVars());
        SDL_Color highlightColor = ParseVar("highlight_color", conf, root->GetVars());
        SDL_Color borderColor = ParseVar("border_color", conf, root->GetVars());
        FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
        std::string text = conf->Get("text").get<std::string>();
        SDL_Color textColor = ParseVar("text_color", conf, root->GetVars());

        ButtonProp prop = {
                            dimr,
                            backgroundColor,
                            highlightColor,
                            borderColor,
                            font,
                            text,
                            textColor,
                            align
                        };

        Button *newb = new Button(sid, prop);

        sid.parent->Add(newb);

        newb->InternalInit();
    }
}

void Button::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Button::Begin({root->GetCurrent(), name});
}

void Button::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Button::Begin({root->GetCurrent(), name});
    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Button::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Button::Begin(ShapeId sid, ButtonProp prop)
{
    Button *newb = new Button(sid, prop);

    Root *root = &Root::GetInstance();
    root->GetCurrent()->Add(newb);

    ((Button *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

ButtonProp Button::GetProp()
{
    return prop;
}

void Button::Draw()
{
    if (!hidden)
    {
        if (mouseOver)
        {
            SDL_SetRenderDrawColor(Window::GetRenderer(), prop.highlightColor.r, prop.highlightColor.g, prop.highlightColor.b, prop.highlightColor.a);
        }
        else
        {
            SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r, prop.backgroundColor.g, prop.backgroundColor.b, prop.backgroundColor.a);
        }

        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r, prop.borderColor.g, prop.borderColor.b, prop.borderColor.a);
        SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);

        for (Shape *w : shapes)
        {
            w->Draw();
        }
    }
}

void Button::Update(SDL_Event *e)
{
    if (!hidden)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        static int nr = 0;
        if (e->type == SDL_MOUSEBUTTONUP)
        {

            if (PointInRect({x, y}, rect))
            {
                if (onClickCallback != nullptr)
                {
                    onClickCallback();
                    SDL_PollEvent(e);
                }
            }
        }

        if (highlight)
        {
            if (PointInRect({x, y}, rect))
            {
                mouseOver = true;
            }
            else
            {
                mouseOver = false;
            }
        }
    }
}

int Button::GetTextSize()
{
    return textSize;
}

std::string Button::GetText()
{
    Root *root = &Root::GetInstance();
    Text *to = (Text *)(Button *)root->GetCurrent()->Get(name)->Get(this->name + "_text");
    return to->GetText();
}

void Button::SetText(std::string text)
{
    Root *root = &Root::GetInstance();

    if (this->prop.text == "")
    {
        delete shapes[0];
        shapes.clear();
        shapesNames.clear();

        this->prop.text = text;

        InternalInit();
    }

    Text *to = (Text *)((Button *)root->GetCurrent()->Get(name))->Get(this->name + "_text");

    to->SetText(text);
    this->prop.text = text;
}

void Button::InternalInit()
{
    // child text
    Root *root = &Root::GetInstance();
    Button *newb = (Button *)root->GetCurrent()->Get(name);

    Text::Begin({newb, name + "_text"}, {prop.font, prop.text}, GetRect().x + GetRect().w / 20, GetRect().y, {0, 0, 0, 255});

    Text *to = (Text *)newb->Get(name + "_text");
    to->SetColor({newb->GetProp().textColor});
    textSize = to->GetWidth();

    to->SetX(newb->GetRect().x + rect.w / 20);

    if (prop.align.valign == V::TOP)
    {
        if (prop.align.halign == H::MID)
        {
            to->SetX(newb->GetHalfX() - to->GetWidth() / 2);
        }
        else if (prop.align.halign == H::RIGHT)
        {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
    }
    else if (prop.align.valign == V::MID)
    {
        if (prop.align.halign == H::MID)
        {
            to->SetX(newb->GetHalfX() - to->GetWidth() / 2);
        }
        else if (prop.align.halign == H::RIGHT)
        {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
        to->SetY(newb->GetHalfY() - to->GetHeight() / 2);
    }
    else if (prop.align.valign == V::BOTTOM)
    {
        if (prop.align.halign == H::MID)
        {
            to->SetX(newb->GetHalfX() - to->GetWidth() / 2);
        }
        else if (prop.align.halign == H::RIGHT)
        {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
        to->SetY(newb->GetRect().y + newb->GetRect().h - to->GetHeight());
    }
}

void Button::SetHighlight(bool state)
{
    highlight = state;
}