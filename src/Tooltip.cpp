#include "Tooltip.h"
#include "Root.h"

using namespace PaceLib;

Tooltip::Tooltip(ShapeId sid, TooltipProp prop)
{
    this->prop = prop;

    this->parent = sid.parent;

    SDL_Rect child = sid.parent->GetRect();

    child.x = child.x + sid.parent->GetRect().w / 2;
    child.y = child.y + sid.parent->GetRect().h / 2;

    rect = child;

    hidden = false;

    this->name = sid.name;

    wtype = WidgetType::TOOLTIP;

    textSize = 0;

    this->color = prop.backgroundColor;
    this->borderColor = prop.borderColor;

    this->name = sid.name;
}

void Tooltip::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_ToolTip.conf";
    if (std::filesystem::exists(path))
    {
        Configuration *conf = new Configuration(path);

        Tooltip *dt;

        TooltipProp prop = LoadTooltipProp(conf);

        if (conf->Get("backgroundColor") == "parent")
        {
            prop.backgroundColor = sid.parent->GetColor();
        }

        dt = new Tooltip(sid, prop);
        sid.parent->Add(dt);

        dt->InternalInit();
    }
}

void Tooltip::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Tooltip::Begin({root->GetCurrent(), name});
}

void Tooltip::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Tooltip::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Tooltip::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tooltip::Begin(ShapeId sid, TooltipProp prop)
{
    Tooltip *dt = new Tooltip(sid, prop);
    sid.parent->Add(dt);

    dt->InternalInit();
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

            SDL_SetRenderDrawColor(Window::GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(Window::GetRenderer(), &rect);

            for (Shape *w : shapes)
            {
                w->Draw();
            }
        }
    }
}

void Tooltip::InternalInit()
{
     // child text
    Root *root = &Root::GetInstance();
    Tooltip *dt = (Tooltip *)root->GetCurrent()->Get(name);

    TextProp tprop = {
         dt->GetRect().x + dt->GetRect().w / 20,
         dt->GetRect().y,
         prop.font,
         prop.text,
         prop.textColor
    };

    Text::Begin({dt, dt->name+"_text"}, tprop);

    Text *to = (Text *)dt->Get(name + "_text");

    to->SetX(dt->GetRect().x);
    to->SetY(dt->GetRect().y);

    textSize = to->GetWidth();
    rect.w = textSize;
}

TooltipProp Tooltip::LoadTooltipProp(Configuration *conf)
{
    Root *root = &Root::GetInstance();

    SDL_Color backgroundColor = Widget::ParseVar("background", conf, root->GetVars());
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
    FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
    std::string text = conf->Get("text").get<std::string>();
    SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());

    TooltipProp prop = {
                        font,
                        text,
                        textColor,
                        backgroundColor,
                        borderColor
                    };
    return prop;
}