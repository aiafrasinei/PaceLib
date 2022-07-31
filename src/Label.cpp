#include "Label.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

Label::Label(ShapeId sid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID})
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
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    to = Text::Begin(fto.font, fto.text, rect.x, rect.y, textColor);
    InternalAlign(align);

    this->name = sid.name;

    wtype = WidgetType::LABEL;
}

Label::~Label()
{

}

void Label::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

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

        Label *lb = nullptr;
        if (conf->Get("color") == "parent") {
            lb = new Label( sid, 
                {{dim[0], dim[1], dim[2], dim[3]},
                {sid.parent->GetColor().r, sid.parent->GetColor().g, sid.parent->GetColor().b, sid.parent->GetColor().a}},
                {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
                align);

        } else {
            lb = new Label( sid, 
                {{dim[0], dim[1], dim[2], dim[3]},
                {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}},
                {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()},
                align);
        }

        lb->SetTextColor({conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});

        lb->conf = conf;
        sid.parent->Add(lb);
    }
}

void Label::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    Label::Begin({root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->Get(root->GetCurrent()->name)->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }
}

void Label::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Label::Begin(ShapeId sid, PropDimColor dco, PropFontText fto, Align align)
{
    sid.parent->Add(new Label( sid, dco, fto, align ));
}

void Label::InternalAlign(Align align)
{
    if(align.valign == V::TOP) {
        if (align.halign == H::MID) {
            to->SetX(this->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(this->rect.x + this->rect.w - to->GetWidth());
        }
    } else if (align.valign == V::MID) {
        if (align.halign == H::MID) {
            to->SetX(this->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(this->rect.x + this->rect.w - to->GetWidth());
        }
        to->SetY(this->GetHalfY() - to->GetHeight()/2);
    } else if (align.valign == V::BOTTOM) {
        if (align.halign == H::MID) {
            to->SetX(this->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(this->rect.x + this->rect.w - to->GetWidth());
        }
        to->SetY(this->rect.y + this->rect.h - to->GetHeight());
    }
}

void Label::SetTextAlign(Align align)
{
    this->align = align;
}

void Label::SetTextColor(SDL_Color color)
{
    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a;

    to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
}

void Label::Draw()
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
