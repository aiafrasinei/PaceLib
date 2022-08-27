#include "Label.h"
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

    this->name = sid.name;

    wtype = WidgetType::LABEL;

    this->fto = fto;
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

        PropFontText fto = {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>()};

        Label *newl = new Label( sid, 
            {{dim[0], dim[1], dim[2], dim[3]},
            {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}},
            fto,
            align);

        newl->SetTextColor({conf->Get("text_color")[0], conf->Get("text_color")[1], conf->Get("text_color")[2], conf->Get("text_color")[3]});
        newl->conf = conf;

        sid.parent->Add(newl);

        newl->InternalInit();
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

void Label::Begin(ShapeId sid, PropDimColor dco, PropFontText fto, Align align)
{
    Label *newl = new Label(sid, dco, fto, align);
    newl->InternalInit();
    sid.parent->Add(newl); 
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

    /*Root *root = &Root::GetInstance();
    Text *to = (Text *)root->GetLabel(this->name)->Get(this->name + "_text");
    to->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);*/
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
    }
}

void Label::InternalInit()
{
    //child text
    Root *root = &Root::GetInstance();
    Label *newb = (Label *)root->GetCurrent()->Get(name);

    Text::Begin( {newb, name+"_text"}, fto, GetRect().x + GetRect().w/10, GetRect().y, {0,0,0,255});

    Text *to = (Text *)newb->Get(name + "_text");
    to->SetColor(newb->GetTextColor());
    
    to->SetX(newb->GetRect().x + rect.w/20);

    if(align.valign == V::TOP) {
        if (align.halign == H::MID) {
            to->SetX(newb->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
    } else if (align.valign == V::MID) {
        if (align.halign == H::MID) {
            to->SetX(newb->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
        to->SetY(newb->GetHalfY() - to->GetHeight()/2);
    } else if (align.valign == V::BOTTOM) {
        if (align.halign == H::MID) {
            to->SetX(newb->GetHalfX() - to->GetWidth()/2);
        } else if (align.halign == H::RIGHT) {
            to->SetX(newb->GetRect().x + newb->GetRect().w - to->GetWidth());
        }
        to->SetY(newb->GetRect().y + newb->GetRect().h - to->GetHeight());
    }
}

SDL_Color Label::GetTextColor()
{
    return textColor;
}