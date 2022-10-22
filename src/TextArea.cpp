#include "TextArea.h"
#include "Root.h"

using namespace PaceLib;

TextArea::TextArea(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align={V::MID, H::MID})
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

    this->align = align;
    
    color = { dco.color.r, dco.color.g, dco.color.b, dco.color.a };

    textColor = {0, 0, 0 , 255};

    textSpacing = 20;

    this->name = sid.name;

    wtype = WidgetType::TEXTAREA;

    this->tarr = tarr;

    this->font = font;
}

TextArea::~TextArea()
{

}

void TextArea::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_TextArea.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        int dim[4];
        Widget::ParseDim(dim, conf);

        Root *root = &Root::GetInstance();
        SDL_Color color = ParseVar("color", conf, root->GetVars());

        PropDimColor dco = {{dim[0], dim[1], dim[2], dim[3]}, color};
        FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
    
        Align align;
        if(conf->Get("align")[0] == "mid") {
            align.valign = V::MID;
        } else if(conf->Get("align")[0] == "top") {
            align.valign = V::TOP;
        } else if(conf->Get("align")[0] == "bottom") {
            align.valign = V::BOTTOM;
        }

        if(conf->Get("align")[1] == "left") {
            align.halign = H::LEFT;
        } else if(conf->Get("align")[1] == "mid") {
            align.halign = H::MID;
        } else if(conf->Get("align")[1] == "right") {
            align.halign = H::RIGHT;
        }

        TextArea *ta = new TextArea(sid, dco , font, conf->Get("text_arr").get<std::vector<std::string>>(), align);
        sid.parent->Add(ta);

        SDL_Color text_color = ParseVar("text_color", conf, root->GetVars());
        ta->SetTextColor(text_color);
        
        ta->conf = conf;

        ta->InternalInit();
    }
}

void TextArea::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    TextArea::Begin({root->GetCurrent(), name});
}

void TextArea::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    TextArea::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void TextArea::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void TextArea::Begin(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align)
{
    TextArea *ta = new TextArea(sid, dco, font, tarr, align);
    sid.parent->Add(ta);

    Root *root = &Root::GetInstance();
    ((TextArea *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

void TextArea::SetTextAlign(Align align)
{
    this->align = align;
}

void TextArea::SetTextColor(SDL_Color color)
{
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;
}

void TextArea::Draw()
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

void TextArea::SetTextSpacing(int size)
{
    this->textSpacing = size;
}

SDL_Color TextArea::GetTextColor()
{
    return textColor;
}

void TextArea::InternalInit()
{
    Root *root = &Root::GetInstance();
    TextArea *ta = (TextArea *)root->GetCurrent()->Get(name);

    int ry = rect.y;
    int i=0;
    for (std::string text : tarr) {
        Text::Begin({ta, ta->name+"_text" + std::to_string(i)}, {font, text}, rect.x + rect.w/50, ry, {textColor.r, textColor.g, textColor.b, textColor.a});

        Text *to = (Text *)ta->Get(name + "_text" + std::to_string(i));
        to->SetColor({ta->GetTextColor()});
        to->SetX(GetRect().x + rect.w/20);
        to->SetY(ry);

        ry = ry + 20;
        i++;
    }

    
}