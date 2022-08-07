#include "TextArea.h"
#include "Window.h"
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

    int ry = rect.y;
    for (std::string text : tarr) {
        tos.push_back(Text::Begin(font, text, rect.x + rect.w/50, ry, {textColor.r, textColor.g, textColor.b, textColor.a}));
        ry = ry + 20;
    }

    this->name = sid.name;

    wtype = WidgetType::TEXTAREA;
}

TextArea::~TextArea()
{

}

void TextArea::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropDimColor dco = {{dim[0], dim[1], dim[2], dim[3]}, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}};
        FC_Font *font = Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
        
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

        sid.parent->Add(new TextArea(sid, dco , font, conf->Get("text_arr").get<std::vector<std::string>>(), align));
    }
}

void TextArea::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    TextArea::Begin({root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->GetCurrent()->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }
}

void TextArea::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void TextArea::Begin(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align)
{
    sid.parent->Add(new TextArea(sid, dco, font, tarr, align));
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