#include "ComboBox.h"
#include <functional>
#include "Root.h"
#include "Triangle.h"
#include <algorithm>

using namespace PaceLib;

ComboBox::ComboBox(ShapeId sid, MultiItemsProp prop)
{
    this->prop = prop;
    rect = prop.rect;

    if (sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.rect.y;
    }

    this->prop.rect = rect;
    color = prop.backgroundColor;
    borderColor = prop.borderColor;

    hidden = false;

    mouseOver = false;

    wtype = WidgetType::COMBOBOX;

    onClickCallback = nullptr;

    textSize = 0;

    selected = -1;
    mainRendererSelected = false;
    this->name = sid.name;
}

ComboBox::~ComboBox()
{
}

void ComboBox::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_ComboBox.conf";
    if (std::filesystem::exists(path))
    {
        Configuration *conf = new Configuration(path);

        int dim[4];
        Root::ParseDim(dim, conf);

        Root *root = &Root::GetInstance();

        SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
        SDL_Color backgroundColor = Widget::ParseVar("background", conf, root->GetVars());
        SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
        FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
        SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());
        std::vector<std::string> tarr = conf->Get("text_arr").get<std::vector<std::string>>();

        MultiItemsProp prop = {
                            dimr,
                            font,
                            tarr,
                            textColor,
                            backgroundColor,
                            borderColor
                        };

        ComboBox *newcb = new ComboBox(sid, prop);

        sid.parent->Add(newcb);

        newcb->AddItems(tarr);
    }
}

void ComboBox::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    ComboBox::Begin({root->GetCurrent(), name});

    Configuration *conf = new Configuration("wconfs/" + name + "_ComboBox.conf");
    ComboBox *curr = ((ComboBox *)root->GetCurrent()->Get(name));
    SDL_Rect currRect = curr->GetRect();
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());

    Triangle::Begin({root->GetCurrent()->Get(name), name + "_triangle_decorator"},
    0, currRect.h,
    currRect.w, currRect.h,
    currRect.w/2, currRect.h + currRect.h/3,
    borderColor);
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

void ComboBox::Begin(ShapeId sid, MultiItemsProp prop)
{
    ComboBox *newcb = new ComboBox(sid, prop);

    Root *root = &Root::GetInstance();
    root->GetCurrent()->Add(newcb);

    ComboBox *combo = ((ComboBox *)root->GetCurrent()->Get(sid.name));
    combo->AddItems(prop.tarr);
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
        SDL_Rect r = {newcb->GetRect().x, newcb->GetRect().y+(i*newcb->GetRect().h), newcb->GetRect().w, newcb->GetRect().h};
        LabelProp prop = { r,
                    Root::GetInstance().GetScene("Default")->GetFont("default"),
                    items[i],
                    {0, 0, 0, 255},
                    {H::MID},
                    newcb->GetColor(),
                    {0, 0, 0, 255},
                    {130, 130, 130, 255}
                    };

        Button::Begin({root->GetCurrent(), GetName() + ":" + "item_" + std::to_string(i)}, prop);
        root->GetCurrent()->Get(GetName() + ":" + "item_" + std::to_string(i))->Hide();
    }

    LabelProp prop = { newcb->GetRect(),
                    Root::GetInstance().GetScene("Default")->GetFont("default"),
                    "",
                    {0, 0, 0, 255},
                    {H::MID},
                    newcb->GetColor(),
                    {0, 0, 0, 255},
                    {130, 130, 130, 255} };

    Button::Begin({root->GetCurrent(), GetName() + ":" + "main_item_renderer"}, prop);

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
