#include "Text.h"
#include "Window.hpp"
#include "Root.h"

using namespace PaceLib;

Text::Text(ShapeId sid, TextProp prop)
{
    this->prop = prop;

    if(sid.parent->name != "root") {
        this->prop.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.x;
        this->prop.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.y;
    }

    hidden = false;

    this->name = sid.name;

    wtype = WidgetType::TEXT;

    rect = FC_DrawColor(prop.font, Window::GetRenderer(), prop.x, prop.y, prop.color, prop.text.c_str());

}

Text::~Text()
{

}

void Text::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Text.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        TextProp prop = LoadTextProp(conf);

        Text *t = new Text(sid, prop);

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

    Widget *c = ((Widget *)root->GetCurrent());
    root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Text::EndBlock()
{
    Root *root = &Root::GetInstance();

    Widget *c = ((Widget *)root->GetCurrent());
    root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Text::Begin(ShapeId sid, TextProp prop)
{
    Text *txt = new Text(sid, prop);

    sid.parent->Add(txt);
}

void Text::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g, prop.color.b, prop.color.a);
        rect = FC_DrawColor(prop.font, Window::GetRenderer(), prop.x, prop.y, prop.color, prop.text.c_str());
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
    prop.x = x;
}

void Text::SetY(int y)
{
    prop.y = y;
}

std::string Text::GetText()
{
    return prop.text;
}

void Text::SetText(std::string text)
{
    prop.text = text;
}

void Text::SetFont(FC_Font *font)
{
    prop.font = font;
}

TextProp Text::LoadTextProp(Configuration *conf)
{
    int pos[2];
    Widget::ParsePos(pos, conf);

    Root *root = &Root::GetInstance();

    FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
    std::string text = conf->Get("text").get<std::string>();
    SDL_Color color = Widget::ParseVar("color", conf, root->GetVars());

    TextProp prop = {
                        pos[0],
                        pos[1],
                        font,
                        text,
                        color
                    };

    return prop;
}
