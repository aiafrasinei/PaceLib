#include "TextInput.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

TextInput::TextInput(ShapeId sid, PropDimColor dco, PropFontText fto)
{
    if(sid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dco.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dco.rect.y;
    }
    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    Text::Begin({sid.parent, sid.name + "_text"}, fto, rect.x, rect.y, textColor);

    this->name = sid.name;

    wtype = WidgetType::TEXTINPUT;

    this->focus = false;
}

TextInput::~TextInput()
{

}

void TextInput::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropDimColor dco = {{dim[0], dim[1], dim[2], dim[3]},
            {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}};
        PropFontText fto = {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()};
        
        sid.parent->Add(new TextInput(sid, dco, fto));
    }
}

void TextInput::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    TextInput::Begin({root->GetCurrent(), name});
}

void TextInput::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    TextInput::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void TextInput::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void TextInput::Begin(ShapeId sid, PropDimColor dco, PropFontText fto)
{
    sid.parent->Add(new TextInput( sid, dco, fto));
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
    }
}

void TextInput::Update(SDL_Event *e)
{
    if(focus) {
        Root *root = &Root::GetInstance();
        Text *to = (Text *)root->GetLabel(name)->Get(name+"_text");
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
    Root *root = &Root::GetInstance();
    Text *to = (Text *)root->GetLabel(name)->Get(name+"_text");
    return to->GetText();
}