#include "TextInput.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

TextInput::TextInput(WidgetId wid, PropDimColor dco, PropFontText fto)
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
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    to = Text::Create(fto.font, fto.text, rect.x, rect.y, textColor);

    this->name = wid.name;

    wtype = WidgetType::TEXTINPUT;
}

TextInput::~TextInput()
{

}

void TextInput::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropDimColor dco = {{dim[0], dim[1], dim[2], dim[3]},
            {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}};
        PropFontText fto = {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()};
        
        wid.parent->Add(new TextInput(wid, dco, fto));
    }
}

void TextInput::Create(WidgetId wid, PropDimColor dco, PropFontText fto)
{
    wid.parent->Add(new TextInput( wid, dco, fto));
}

void TextInput::Create(WidgetId wid, SDL_Rect dim, std::string text)
{
    wid.parent->Add(new TextInput( wid, {dim, {120, 120, 120, 255}}, {Root::GetInstance().GetScene("Default").GetFont("default"), text}));
}

void TextInput::Create(WidgetId wid, SDL_Rect dim)
{
    wid.parent->Add(new TextInput( wid, {dim, {120, 120, 120, 255}}, {Root::GetInstance().GetScene("Default").GetFont("default"), ""}));
}

void TextInput::SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    textColor.r = r;
    textColor.g = g;
    textColor.b = b;
    textColor.a = a;
}

void TextInput::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
 
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);

        for(Shape *w : shapes) {
            w->Draw();
        }

        SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
        to->Draw();
    }
}

void TextInput::Update(SDL_Event *e)
{
    if(focus) {
        if(e->type == SDL_TEXTINPUT)
        {
            to->SetText(to->GetText() + e->text.text);
        }

        if(e->type == SDL_KEYDOWN)
        {
            char keyDown = e->key.keysym.scancode;
            if(keyDown == SDL_SCANCODE_BACKSPACE) {
                to->SetText(to->GetText().substr(0, to->GetText().size()-1));
            }
        }
    }

    if(e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(PointInRect({x, y}, rect)) {
            focus = !focus;
        } else {
            focus = false;
        }
    }

    for(Shape *s : shapes) {
        s->Update(e);
    }
}

std::string TextInput::GetText()
{
    return to->GetText();
}