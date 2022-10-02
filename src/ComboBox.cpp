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
