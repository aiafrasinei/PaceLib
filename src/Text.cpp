#include "Text.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Text::Text(ShapeId sid, PropFontText fto, int x, int y, SDL_Color color)
{
    this->font = fto.font;
    this->text = fto.text;
     if(sid.parent->name == "root") {
        this->x = x;
        this->y = y;
    } else {
        this->x = static_cast<Widget *>(sid.parent)->GetRect().x + x;
        this->y = static_cast<Widget *>(sid.parent)->GetRect().y + y;
    }

    SetColor(color.r, color.g, color.b, color.a);

    hidden = false;

    rect = FC_DrawColor(fto.font, Window::GetRenderer(), this->x, this->y, color, text.c_str());

    this->name = sid.name;
}

Text::~Text()
{

}

void Text::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int pos[2];
        Widget::ParsePos(pos, conf);

        Text *t = new Text(sid, 
        {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
        pos[0], pos[1],
        {conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});

        t->conf = conf;
        sid.parent->Add(t);
    }
}

void Text::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Text::Begin({root->GetCurrent(), name});
}

void Text::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Text::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Text::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Text::Begin(ShapeId sid, PropFontText fto, int x, int y, SDL_Color color)
{
    sid.parent->Add(new Text(sid, fto, x, y, color));
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

void Text::SetFont(FC_Font *font)
{
    this->font = font;
}
