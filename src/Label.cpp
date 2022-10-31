#include "Label.h"
#include <functional>
#include "Root.h"
#include "ConLog.hpp"

using namespace PaceLib;

Label::Label(ShapeId sid, LabelProp prop)
{
    this->prop = prop;

    rect = prop.rect;

    if(sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.rect.y;
    }
    
    this->prop.rect = rect;
    color = prop.backgroundColor;
    borderColor = prop.borderColor;

    hidden = false;

    this->name = sid.name;

    wtype = WidgetType::LABEL;

    textSize = 0;
}

Label::Label()
{
}

Label::~Label()
{
}

// load all info from conf file ( {dim, color}, {font_name, text}, align )
void Label::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Label.conf";
    if (std::filesystem::exists(path))
    {
        Configuration *conf = new Configuration(path);

        LabelProp prop = LoadLabelProp(conf);

        Label *newb = new Label(sid, prop);

        sid.parent->Add(newb);

        newb->InternalInit();
    }
}

void Label::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Label::Begin({root->GetCurrent(), name});
}

void Label::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Label::Begin({root->GetCurrent(), name});
    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Label::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Label::Begin(ShapeId sid, LabelProp prop)
{
    Label *newb = new Label(sid, prop);

    Root *root = &Root::GetInstance();
    root->GetCurrent()->Add(newb);

    ((Label *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

LabelProp Label::GetProp()
{
    return prop;
}

void Label::Draw()
{
    if (!hidden)
    {
        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r, prop.backgroundColor.g, prop.backgroundColor.b, prop.backgroundColor.a);
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

int Label::GetTextSize()
{
    return textSize;
}

std::string Label::GetText()
{
    Root *root = &Root::GetInstance();
    Text *to = (Text *)root->GetCurrent()->Get(name)->Get(this->name + "_text");
    return to->GetText();
}

void Label::SetText(std::string text)
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

    Text *to = (Text *)(root->GetCurrent()->Get(name))->Get(this->name + "_text");

    to->SetText(text);
    this->prop.text = text;
}

void Label::InternalInit()
{
    // child text
    Root *root = &Root::GetInstance();
    Label *newb = (Label *)root->GetCurrent()->Get(name);

    TextProp tprop = {
         GetRect().x + GetRect().w / 20,
         GetRect().y,
         prop.font,
         prop.text,
         prop.textColor
    };

    Text::Begin({newb, name + "_text"}, tprop);

    Text *to = (Text *)newb->Get(name + "_text");
    to->SetColor({newb->GetProp().textColor});
    textSize = to->GetWidth();

    SetTextAlign(prop.align);
}

void Label::SetTextAlign(HorizontalAlign align)
{
    Text *to = (Text *)this->Get(name + "_text");

    to->SetY(GetHalfY() - to->GetHeight()/2);

    if (align.halign == H::MID) {
        to->SetX(GetHalfX() - to->GetWidth() / 2);
    } else if (align.halign == H::RIGHT) {
        to->SetX(GetRect().x + GetRect().w - to->GetWidth() - rect.w / 20);
    } else if (align.halign == H::LEFT) {
        to->SetX(GetRect().x + rect.w / 20);
    }
}

LabelProp Label::LoadLabelProp(Configuration *conf)
{
    int dim[4];
    Widget::ParseDim(dim, conf);

    HorizontalAlign align;
    if (conf->Get("align") == "left")
        align.halign = H::LEFT;
    else if (conf->Get("align") == "mid")
        align.halign = H::MID;
    else if (conf->Get("align") == "right")
        align.halign = H::RIGHT;

    Root *root = &Root::GetInstance();

    SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
    SDL_Color backgroundColor = Widget::ParseVar("background", conf, root->GetVars());
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
    SDL_Color highlightColor = Widget::ParseVar("highlight", conf, root->GetVars());
    FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
    std::string text = conf->Get("text").get<std::string>();
    SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());

    LabelProp prop = {
                        dimr,
                        font,
                        text,
                        textColor,
                        align,
                        backgroundColor,
                        borderColor,
                        highlightColor
                    };
    return prop;
}
