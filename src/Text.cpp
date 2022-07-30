#include "Text.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Text::Text(ShapeId wid, PropFontText fto, int x, int y, SDL_Color color)
{
    this->font = fto.font;
    this->text = fto.text;
     if(wid.parent->name == "root") {
        this->x = x;
        this->y = y;
    } else {
        this->x = static_cast<Widget *>(wid.parent)->GetRect().x + x;
        this->y = static_cast<Widget *>(wid.parent)->GetRect().y + y;
    }

    SetColor(color.r, color.g, color.b, color.a);

    hidden = false;

    rect = FC_DrawColor(fto.font, Window::GetRenderer(), this->x, this->y, color, text.c_str());

    this->name = wid.name;
}

Text::Text(FC_Font *font, int x, int y, SDL_Color color, std::string text)
{
    this->font = font;
    this->text = text;
    this->x = x;
    this->y = y;

    SetColor(color.r, color.g, color.b, color.a);

    hidden = false;

    rect = FC_DrawColor(font, Window::GetRenderer(), x, y, color, text.c_str());
}

Text::~Text()
{

}

void Text::Create(ShapeId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int pos[2];
        Widget::ParsePos(pos, conf);

        Text *t = new Text(wid, 
        {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
        pos[0], pos[1],
        {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});

        t->conf = conf;
        wid.parent->Add(t);
    }
}

void Text::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    Text::Create({(Widget *)root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->Get(root->GetCurrent()->name)->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }

}

void Text::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Text::Create(ShapeId wid, PropFontText fto, int x, int y, SDL_Color color)
{
    wid.parent->Add(new Text(wid, fto, x, y, color));
}

void Text::Create(ShapeId wid, int x, int y, SDL_Color color, std::string text)
{
    wid.parent->Add(new Text(wid, {Root::GetInstance().GetScene("Default").GetFont("default"), text}, x, y, color));
}

Text *Text::Create(FC_Font *font,  std::string text, int x, int y, SDL_Color color)
{
    return new Text(font, x, y, color, text);
}

void Text::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), this->color.r, this->color.g, this->color.b, this->color.a);
        rect = FC_DrawColor(font, Window::GetRenderer(), this->x, this->y, color, text.c_str());
    }
}

int Text::GetWidth()
{
    return rect.w;
}

int Text::GetHeight()
{
    return rect.h;
}

void Text::SetX(int x)
{
    this->x = x;
}

void Text::SetY(int y)
{
    this->y = y;
}

std::string Text::GetText()
{
    return text;
}

void Text::SetText(std::string text)
{
    this->text = text;
}

void Text::SetTextColor(SDL_Color color)
{
    SetColor(color.r, color.g, color.b, color.a);
}