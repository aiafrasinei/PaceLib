#include "ComboBox.h"
#include <functional>
#include "Root.h"
#include "Triangle.h"
#include <algorithm>

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

    selected = -1;
    mainRendererSelected = false;

    borderColor = {0, 0, 0, 255};
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

        Root *root = &Root::GetInstance();
        SDL_Color color = ParseVar("color", conf, root->GetVars());

        PropFontText fto = { root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), conf->Get("text").get<std::string>() };

        ComboBox *newcb = new ComboBox(sid,
                                  {{dim[0], dim[1], dim[2], dim[3]},
                                   color},
                                  fto);

        sid.parent->Add(newcb);

        newcb->AddItems(conf->Get("items").get<std::vector<std::string>>());
    }
}

void ComboBox::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    ComboBox::Begin({root->GetCurrent(), name});

    Configuration *conf = new Configuration("wconfs/" + name + ".conf");
    ComboBox *curr = ((ComboBox *)root->GetCurrent()->Get(name));
    SDL_Rect currRect = curr->GetRect();

    Triangle::Begin({root->GetCurrent()->Get(name), name + "_triangle_decorator"},
    0, currRect.h,
    currRect.w, currRect.h,
    currRect.w/2, currRect.h + currRect.h/3,
    {conf->Get("border_color")[0], conf->Get("border_color")[1], conf->Get("border_color")[2], conf->Get("border_color")[3]});
}

void ComboBox::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    ComboBox::Begin({root->GetCurrent(), name});
    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void ComboBox::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void ComboBox::Begin(ShapeId sid, PropDimColor dco, PropFontText fto, std::vector<std::string> items)
{
    ComboBox *newcb = new ComboBox(sid, dco, fto);

    Root *root = &Root::GetInstance();
    root->GetCurrent()->Add(newcb);

    ComboBox *combo = ((ComboBox *)root->GetCurrent()->Get(sid.name));
    combo->AddItems(items);
}

void ComboBox::Draw()
{
    for (Shape *w : shapes)
    {
        w->Draw();
    }
}

void ComboBox::Update(SDL_Event *e)
{
}

void ComboBox::InternalInit()
{
    Root *root = &Root::GetInstance();
    ComboBox *newcb = (ComboBox *)root->GetCurrent()->Get(name);

    for(int i=0; i<items.size(); i++) {
        Button::Begin({root->GetCurrent(), GetName() + ":" + "item_" + std::to_string(i)}, {{newcb->GetRect().x, newcb->GetRect().y+(i*newcb->GetRect().h), newcb->GetRect().w, newcb->GetRect().h}, newcb->GetColor()}, {Root::GetInstance().GetScene("Default")->GetFont("default"), items[i]}, {V::MID, H::LEFT});
        root->GetCurrent()->Get(GetName() + ":" + "item_" + std::to_string(i))->Hide();
    }

    Button::Begin({root->GetCurrent(), GetName() + ":" + "main_item_renderer"}, {newcb->GetRect(), newcb->GetColor()}, {Root::GetInstance().GetScene("Default")->GetFont("default"), ""}, {V::MID, H::LEFT});

    Button *main_renderer = ((Button *)root->GetCurrent()->Get(GetName() + ":" + "main_item_renderer"));
    main_renderer->onClickCallback = [this, main_renderer, root]() {
        mainRendererSelected = !mainRendererSelected;
        if(mainRendererSelected) {
            if(items.size() > 0) {
                main_renderer->Hide();
                for(int i=0; i<items.size(); i++) {
                    root->GetCurrent()->Get(GetName() + ":" + "item_" + std::to_string(i))->Show();
                }
            }
        } else {
            main_renderer->Show();
        }
    };

    for(int i=0; i<items.size(); i++) {
        Button * current = ((Button *)root->GetCurrent()->Get(GetName() + ":" + "item_" + std::to_string(i)));
        current->onClickCallback = [this, i, main_renderer, current, root]() {
            for(int i=0; i<items.size(); i++) {
                root->GetCurrent()->Get(GetName() + ":" + "item_" + std::to_string(i))->Hide();
            }
            mainRendererSelected = false;

            selected = i;
            main_renderer->SetText(current->GetText());
            main_renderer->Show(); 
        };
    }
}

int ComboBox::GetSelected()
{
    return selected;
}

void ComboBox::SetSelection(int index)
{
    selected = index;

    Root *root = &Root::GetInstance();
    Button *main_renderer = ((Button *)root->GetCurrent()->Get(GetName() + ":" + "main_item_renderer"));
    Button *sel =((Button *)root->GetCurrent()->Get(GetName() + ":" + "item_" + std::to_string(selected)));

    if(items.size() > 0) {
        main_renderer->SetText(sel->GetText());
    }
}

int ComboBox::GetNrItems()
{
    return items.size();
}

void ComboBox::AddItem(std::string item)
{
    items.push_back(item);
    InternalInit();
}

void ComboBox::AddItems(std::vector<std::string> items)
{
    for(int i=0; i<items.size(); i++) {
        this->items.push_back(items[i]);
    }
    InternalInit();
}

void ComboBox::ReplaceItems(std::vector<std::string> items)
{
    this->items = items;
    InternalInit();
}