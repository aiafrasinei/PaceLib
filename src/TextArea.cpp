#include "TextArea.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

TextArea::TextArea(WidgetId wid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align={V::MID, H::MID})
{
    if(wid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = wid.parent->GetRect().x + dco.rect.x;
        rect.y = wid.parent->GetRect().y + dco.rect.y;
    }
    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;

    this->align = align;
    
    color = { dco.color.r, dco.color.g, dco.color.b, dco.color.a };

    textColor = {0, 0, 0 , 255};

    textSpacing = 20;

    int ry = rect.y;
    for (std::string text : tarr) {
        tos.push_back(Text::Create(font, text, rect.x + rect.w/50, ry, {textColor.r, textColor.g, textColor.b, textColor.a}));
        ry = ry + 20;
    }

    this->name = wid.name;

    wtype = WidgetType::TEXTAREA;
}

TextArea::~TextArea()
{

}

void TextArea::Create(WidgetId wid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align)
{
    wid.parent->Add(new TextArea(wid, dco, font, tarr, align));
}

void TextArea::Create(WidgetId wid, PropDimColor dco, std::vector<std::string> tarr, Align align)
{
    wid.parent->Add(new TextArea(wid, dco, Root::GetInstance().GetScene("Default").GetFont("default"), tarr, align));
}

void TextArea::SetTextAlign(Align align)
{
    this->align = align;
}

void TextArea::SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    textColor.r = r;
    textColor.g = g;
    textColor.b = b;
    textColor.a = a;
}

void TextArea::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
 
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        //SDL_SetRenderDrawColor(Window::GetRenderer(), 90, 90, 90, 255);
        //SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        for(Text *to : tos) {
            to->Draw();
        }

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);
        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void TextArea::SetTextSpacing(int size)
{
    this->textSpacing = size;
}