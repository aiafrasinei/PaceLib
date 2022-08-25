#include "Button.h"
#include "Window.h"
#include <functional>
#include "Root.h"

using namespace PaceLib;

Button::Button(ShapeId sid, PropDimColor dco, PropFontText fto, Align align = {V::MID, H::LEFT})
{
    if (sid.parent->name == "root")
    {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    }
    else
    {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dco.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dco.rect.y;
    }

    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;

    this->align = align;

    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    this->name = sid.name;

    mouseOver = false;

    highlight = true;

    Uint8 hr = color.r + 30;
    Uint8 hg = color.g + 30;
    Uint8 hb = color.b + 30;
    Uint8 ha = 255;
    highlightColor = {hr, hg, hb, ha};

    tex = nullptr;

    wtype = WidgetType::BUTTON;

    onClickCallback = nullptr;

    this->fto = fto;

    textSize = 0;
}

Button::~Button()
{
}

// load all info from conf file ( {dim, color}, {font_name, text}, align )
void Button::Begin(ShapeId sid)
{
    if (std::filesystem::exists("wconfs/" + sid.name + ".conf"))
    {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

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

        PropFontText fto = {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()};

        Button *newb = new Button(sid,
                                  {{dim[0], dim[1], dim[2], dim[3]},
                                   {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}},
                                  fto,
                                  align);

        newb->SetTextColor({conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});
        newb->conf = conf;

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

void Button::Begin(ShapeId sid, PropDimColor dco, PropFontText fto, Align align)
{
    Button *newb = new Button(sid, dco, fto, align);

    Root *root = &Root::GetInstance();
    root->GetCurrent()->Add(newb);

    ((Button *)root->GetCurrent()->Get(sid.name))->InternalInit();
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
}

SDL_Color Button::GetTextColor()
{
    return textColor;
}

void Button::Draw()
{
    if (!hidden)
    {
        if (mouseOver)
        {
            SDL_SetRenderDrawColor(Window::GetRenderer(), highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
        }
        else
        {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        }

        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 90, 90, 90, 255);
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
    //    Root *root = &Root::GetInstance();
    //   Text *to = (Text *)((Button *)root->GetCurrent()->Get(name))->Get(this->name + "_text");

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

    if (this->text == "")
    {
        delete shapes[0];
        shapes.clear();
        shapesNames.clear();

        this->text = text;
        this->fto.text = text;

        InternalInit();
    }

    Text *to = (Text *)((Button *)root->GetCurrent()->Get(name))->Get(this->name + "_text");

    to->SetText(text);
    this->text = text;
    this->fto.text = text;
}

void Button::InternalInit()
{
    // child text
    Root *root = &Root::GetInstance();
    Button *newb = (Button *)root->GetCurrent()->Get(name);

    Text::Begin({newb, name + "_text"}, fto, GetRect().x + GetRect().w / 20, GetRect().y, {0, 0, 0, 255});

    Text *to = (Text *)newb->Get(name + "_text");
    to->SetColor({newb->GetTextColor()});
    textSize = to->GetWidth();

    to->SetX(newb->GetRect().x + rect.w / 20);

    if (align.valign == V::TOP)
    {
        if (align.halign == H::MID)
        {
            to->SetX(newb->GetHalfX() - to->GetWidth() / 2);
        }
        else if (align.halign == H::RIGHT)
        {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
    }
    else if (align.valign == V::MID)
    {
        if (align.halign == H::MID)
        {
            to->SetX(newb->GetHalfX() - to->GetWidth() / 2);
        }
        else if (align.halign == H::RIGHT)
        {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
        to->SetY(newb->GetHalfY() - to->GetHeight() / 2);
    }
    else if (align.valign == V::BOTTOM)
    {
        if (align.halign == H::MID)
        {
            to->SetX(newb->GetHalfX() - to->GetWidth() / 2);
        }
        else if (align.halign == H::RIGHT)
        {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
        to->SetY(newb->GetRect().y + newb->GetRect().h - to->GetHeight());
    }
}