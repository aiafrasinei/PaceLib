#include "ComboBox.h"
#include <functional>
#include "Root.h"

using namespace PaceLib;

ComboBox::ComboBox(ShapeId sid, PropDimColor dco, PropFontText fto)
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

ComboBox::~ComboBox()
{
}

void ComboBox::Begin(ShapeId sid)
{
    if (std::filesystem::exists("wconfs/" + sid.name + ".conf"))
    {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropFontText fto = { Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>() };

        ComboBox *newcb = new ComboBox(sid,
                                  {{dim[0], dim[1], dim[2], dim[3]},
                                   {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}},
                                  fto);
    }
}

void ComboBox::Begin(std::string name)
{

}

void ComboBox::Draw()
{
}

void ComboBox::Update(SDL_Event *e)
{
}