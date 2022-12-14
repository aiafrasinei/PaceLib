#include "CheckBox.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

CheckBox::CheckBox(ShapeId sid, LabelProp prop) : Label(sid, prop)
{
    mouseOver = false;

    highlight = true;

    checked = false;

    wtype = WidgetType::CHECKBOX;

    onClickCallback = [this]() {
        if(checked) {
            checked = false;
        } else {
            checked = true;
        }
    };

    midrect = { rect.x+rect.w/4, rect.y+rect.h/4, rect.w/2, rect.h/2 };

    textSize = 0;
}

CheckBox::~CheckBox()
{

}

void CheckBox::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_CheckBox.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        LabelProp prop = LoadLabelProp(conf);

        CheckBox *newc = new CheckBox(sid, prop);

        sid.parent->Add(newc);

        Root *root = &Root::GetInstance();
        ((CheckBox *)root->GetCurrent()->Get(sid.name))->InternalInit();
    }
}


void CheckBox::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    CheckBox::Begin({root->GetCurrent(), name});
}

void CheckBox::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    CheckBox::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);

    Widget *c = ((Widget *)root->GetCurrent());
    root->UpdateAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void CheckBox::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void CheckBox::Begin(ShapeId sid, LabelProp prop)
{
    CheckBox *newc = new CheckBox(sid, prop);
    
    Root *root = &Root::GetInstance();
    root->GetCurrent()->Add(newc);

    ((CheckBox *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

void CheckBox::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        if(checked) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);
            SDL_RenderFillRect(Window::GetRenderer(), &midrect);
        }

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void CheckBox::Update(SDL_Event *e)
{
    if(!hidden) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if(e->type == SDL_MOUSEBUTTONUP)
        {
            if(PointInRect({x, y}, rect)) {
                if(onClickCallback != nullptr) {
                    onClickCallback();
                    SDL_PollEvent(e);
                }
            }
        }

        if(highlight) {
            if(PointInRect({x, y}, rect)) {
                mouseOver = true;
            } else {
                mouseOver = false;
            }
            
        }
    }
}

bool CheckBox::IsChecked()
{
    return checked;
}

void CheckBox::InternalInit()
{
    //child text
    Root *root = &Root::GetInstance();
    CheckBox *newc = (CheckBox *)root->GetCurrent()->Get(name);

    TextProp tprop = {
         newc->GetRect().x + newc->GetRect().w / 10,
         newc->GetRect().y,
         prop.font,
         prop.text,
         prop.textColor
    };

    Text::Begin( {newc, newc->name+"_text"}, tprop);

    Text *to = (Text *)newc->Get(name + "_text");

    textSize = to->GetWidth();

    to->SetX(newc->GetRect().x + 1.5*newc->GetRect().w);
    to->SetY(newc->GetHalfY() - to->GetHeight() / 1.9);
}
