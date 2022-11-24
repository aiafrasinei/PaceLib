#include "Tab.h"
#include "Root.h"

using namespace PaceLib;

Tab::Tab(ShapeId sid, TabProp prop)
{
    this->prop = prop;

    rect = prop.rect;

    if(sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.rect.y;
    }

    this->prop.rect = rect;

    hidden = false;

    this->name = sid.name;

    wtype = WidgetType::TAB;
}

Tab::~Tab()
{

}

void Tab::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Tab.conf";
    if (std::filesystem::exists(path))
    {
        Configuration *conf = new Configuration(path);

        TabProp prop = LoadTabProp(conf);

        Tab *local = new Tab(sid, prop);
        sid.parent->Add(local);
    }
}

void Tab::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Tab::Begin({root->GetCurrent(), name});
}

void Tab::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Tab::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Tab::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tab::Begin(ShapeId sid, TabProp prop)
{
    Tab *local = new Tab(sid, prop);
    sid.parent->Add(local);
}

void Tab::Draw()
{
    if (!hidden)
    {
        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r, prop.backgroundColor.g, prop.backgroundColor.b, prop.backgroundColor.a);
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r, prop.borderColor.g, prop.borderColor.b, prop.backgroundColor.a);
        SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        for (Shape *w : shapes)
        {
            w->Draw();
        }
    }
}

void Tab::Add(Shape *s)
{
    shapes.push_back(s);
}

void Tab::Update(SDL_Event *e)
{
    for (Shape *s : shapes)
    {
        s->Update(e);
    }
}

Button *Tab::GetButton(std::string child)
{
    return static_cast<Button *>(this->Get(child));
}

ButtonTex *Tab::GetButtonTex(std::string child)
{
    return static_cast<ButtonTex *>(this->Get(child));
}

Label *Tab::GetLabel(std::string child)
{
    return static_cast<Label *>(this->Get(child));
}

Widget *Tab::GetWidget(std::string child)
{
    return static_cast<Widget *>(this->Get(child));
}

TabProp Tab::LoadTabProp(Configuration *conf)
{
    int dim[4];
    Root::ParseDim(dim, conf);

    Root *root = &Root::GetInstance();

    SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
    SDL_Color backgroundColor = Widget::ParseVar("background", conf, root->GetVars());
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());

    TabProp prop = {
                        dimr,
                        backgroundColor,
                        borderColor
                    };
    return prop;
}