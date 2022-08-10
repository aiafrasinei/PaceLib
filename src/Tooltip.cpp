#include "Tooltip.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Tooltip::Tooltip(ShapeId sid, SDL_Rect shape, SDL_Color color)
{
    this->parent = sid.parent;

    rect.x = shape.x;
    rect.y = shape.y;
    rect.w = shape.w;
    rect.h = shape.h;

    hidden = false;

    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;
    this->color.a = color.a;

    this->name = sid.name;

    wtype = WidgetType::TOOLTIP;
}

Tooltip::~Tooltip()
{
}

void Tooltip::Begin(ShapeId sid)
{
    if (std::filesystem::exists("wconfs/" + sid.name + ".conf"))
    {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        SDL_Rect child = static_cast<Widget *>(sid.parent)->GetRect();

        sid.parent->Add(new Tooltip(sid, child, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}));
    }
}

void Tooltip::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    Tooltip::Begin({(Widget *)root->GetCurrent(), name});
    if (hasChildren)
    {
        root->SetCurrent(root->GetTooltip(name));
    }
}

void Tooltip::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root);
}

void Tooltip::Begin(ShapeId sid, SDL_Color color, Align align)
{
    SDL_Rect child = static_cast<Widget *>(sid.parent)->GetRect();
    if (align.valign == V::BOTTOM && align.halign == H::MID)
    {
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::BOTTOM && align.halign == H::LEFT)
    {
        child.x = child.x - static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::BOTTOM && align.halign == H::RIGHT)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h;
    }

    if (align.valign == V::TOP && align.halign == H::LEFT)
    {
        child.x = child.x - static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y - static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::TOP && align.halign == H::RIGHT)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y - static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::TOP && align.halign == H::MID)
    {
        child.y = child.y - static_cast<Widget *>(sid.parent)->GetRect().h;
    }

    if (align.valign == V::MID && align.halign == H::LEFT)
    {
        child.x = child.x - static_cast<Widget *>(sid.parent)->GetRect().w;
    }
    else if (align.valign == V::MID && align.halign == H::RIGHT)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w;
    }
    else if (align.valign == V::MID && align.halign == H::MID)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w / 2;
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h / 2;
    }
    sid.parent->Add(new Tooltip(sid, child, color));
}

void Tooltip::Begin(ShapeId sid, int w, int h, SDL_Color color, Align align)
{
    SDL_Rect child = static_cast<Widget *>(sid.parent)->GetRect();

    child.w = w;
    child.h = h;

    if (align.valign == V::BOTTOM && align.halign == H::MID)
    {
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::BOTTOM && align.halign == H::LEFT)
    {
        child.x = child.x - static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::BOTTOM && align.halign == H::RIGHT)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h;
    }

    if (align.valign == V::TOP && align.halign == H::LEFT)
    {
        child.x = child.x - static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y - static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::TOP && align.halign == H::RIGHT)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w;
        child.y = child.y - static_cast<Widget *>(sid.parent)->GetRect().h;
    }
    else if (align.valign == V::TOP && align.halign == H::MID)
    {
        child.y = child.y - static_cast<Widget *>(sid.parent)->GetRect().h;
    }

    if (align.valign == V::MID && align.halign == H::LEFT)
    {
        child.x = child.x - static_cast<Widget *>(sid.parent)->GetRect().w;
    }
    else if (align.valign == V::MID && align.halign == H::RIGHT)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w;
    }
    else if (align.valign == V::MID && align.halign == H::MID)
    {
        child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w / 2;
        child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h / 2;
    }

    sid.parent->Add(new Tooltip(sid, child, color));
}

void Tooltip::Draw()
{
    if (!hidden)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (PointInRect({x, y}, static_cast<Widget *>(parent)->GetRect()))
        {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

            SDL_RenderFillRect(Window::GetRenderer(), &rect);

            for (Shape *w : shapes)
            {
                w->Draw();
            }

            SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b, Window::GetBackgroundColor().a);
        }
    }
}

void Tooltip::Add(Shape *s)
{
    shapes.push_back(s);
}

void Tooltip::Update(SDL_Event *e)
{
    for (Shape *s : shapes)
    {
        s->Update(e);
    }
}

DefaultTooltip::DefaultTooltip(ShapeId sid, PropFontText fto, SDL_Color color, SDL_Color textColor)
{
    this->parent = sid.parent;

    SDL_Rect child = static_cast<Widget *>(sid.parent)->GetRect();

    child.x = child.x + static_cast<Widget *>(sid.parent)->GetRect().w / 2;
    child.y = child.y + static_cast<Widget *>(sid.parent)->GetRect().h / 2;

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

    to = Text::Begin(fto.font, fto.text, rect.x, rect.y, textColor);
    to->SetX(this->GetHalfX() - to->GetWidth() / 2);
}

void DefaultTooltip::Begin(ShapeId sid)
{
    if (std::filesystem::exists("wconfs/" + sid.name + ".conf"))
    {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        if (conf->Get("color") == "parent")
        {
            sid.parent->Add(new DefaultTooltip(sid, {Root::GetInstance().GetScene("Default")->GetFont("default"), conf->Get("text").get<std::string>()}, sid.parent->GetColor(), {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]}));
        }
        else
        {
            sid.parent->Add(new DefaultTooltip(sid, {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()}, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}, {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]}));
        }
    }
}

void DefaultTooltip::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    DefaultTooltip::Begin({root->GetCurrent(), name});
}

void DefaultTooltip::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    DefaultTooltip::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void DefaultTooltip::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void DefaultTooltip::Begin(ShapeId sid, PropFontText fto, SDL_Color color, SDL_Color text_color)
{
    sid.parent->Add(new DefaultTooltip(sid, fto, color, {0, 0, 0, 255}));
}

void DefaultTooltip::Draw()
{
    if (!hidden)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (PointInRect({x, y}, static_cast<Widget *>(parent)->GetRect()))
        {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);

            SDL_RenderFillRect(Window::GetRenderer(), &rect);

            for (Shape *w : shapes)
            {
                w->Draw();
            }

            SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b, Window::GetBackgroundColor().a);

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