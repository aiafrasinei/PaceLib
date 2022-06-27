#include "Text.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Text::Text(WidgetId wid, PropFontText fto, float x, float y, SDL_Color color)
{
    this->font = fto.font;
    this->text = fto.text;
     if(wid.parent->name == "root") {
        this->x = x;
        this->y = y;
    } else {
        this->x = wid.parent->GetRect().x + x;
        this->y = wid.parent->GetRect().y + y;
    }

    SetColor(color.r, color.g, color.b, color.a);

    hidden = false;

    rect = FC_DrawColor(fto.font, Window::GetRenderer(), this->x, this->y, color, text.c_str());

    this->name = wid.name;
}

Text::Text(FC_Font *font, float x, float y, SDL_Color color, std::string text)
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

void Text::Create(WidgetId wid)
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

void Text::Create(WidgetId wid, PropFontText fto, float x, float y, SDL_Color color)
{
    wid.parent->Add(new Text(wid, fto, x, y, color));
}

void Text::Create(WidgetId wid, float x, float y, SDL_Color color, std::string text)
{
    wid.parent->Add(new Text(wid, {Root::GetInstance().GetScene("Default").GetFont(0), text}, x, y, color));
}

Text *Text::Create(FC_Font *font,  std::string text, float x, float y, SDL_Color color)
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

float Text::GetWidth()
{
    return rect.w;
}

float Text::GetHeight()
{
    return rect.h;
}

void Text::SetX(float x)
{
    this->x = x;
}

void Text::SetY(float y)
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