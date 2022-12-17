#include "ButtonTex.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

ButtonTex::ButtonTex(ShapeId sid, ButtonTexProp prop)
{
    this->prop = prop;

    rect = prop.normal.rect;

    if(sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.normal.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.normal.rect.y;
    }
    
    this->prop.normal.rect = rect;
    borderColor = prop.borderColor;

    hidden = false;

    this->name = sid.name;

    mouseOver = false;

    highlight = true;

    wtype = WidgetType::BUTTONTEX;
}

ButtonTex::~ButtonTex()
{

}

void ButtonTex::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_ButtonTex.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        ButtonTexProp prop = LoadButtonTexProp(conf);

        std::string scene_name = conf->Get("scene").get<std::string>();

        ButtonTex *btex = nullptr;
        if(conf->Get("over_tex_name").get<std::string>() == "") {
            TexProp nullp = {nullptr, {0,0,0,255}};
            prop.over = nullp;
            btex = new ButtonTex(sid, prop);
        } else {
            btex = new ButtonTex(sid, prop);
        }

        btex->conf = conf;
        if(btex != nullptr) {
            sid.parent->Add(btex);
        }
    }
}

void ButtonTex::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    ButtonTex::Begin({root->GetCurrent(), name});
}

void ButtonTex::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    ButtonTex::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);

    Widget *c = ((Widget *)root->GetCurrent());
    root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void ButtonTex::EndBlock()
{
    Root *root = &Root::GetInstance();

    Widget *c = ((Widget *)root->GetCurrent());
    root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

    root->SetCurrent(root->GetCurrent()->GetParent());
}

void ButtonTex::Begin(ShapeId sid, ButtonTexProp prop)
{
    sid.parent->Add(new ButtonTex(sid, prop));
}

void ButtonTex::Draw()
{
    if(!hidden) {
        if(mouseOver) {
            //SDL_SetRenderDrawColor(Window::GetRenderer(), prop.highlightColor.r, prop.highlightColor.g, prop.highlightColor.b, prop.highlightColor.a);
            if(prop.over.tex == nullptr) {
                SDL_SetTextureColorMod( prop.normal.tex, prop.highlightColor.r, prop.highlightColor.g, prop.highlightColor.b );
            }
        } else {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        }

        if(prop.drawBorder) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(Window::GetRenderer(), &rect);
        }

        SDL_RenderCopy(Window::GetRenderer(), prop.normal.tex, nullptr, &prop.normal.rect);
        if(prop.over.tex == nullptr) {
            SDL_SetTextureColorMod(prop.normal.tex, 255, 255, 255);
        }

        if(mouseOver) {
            if(prop.over.tex != nullptr) {
                SDL_RenderCopy(Window::GetRenderer(), prop.over.tex, nullptr, &prop.over.rect);
            }
        }

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void ButtonTex::Update(SDL_Event *e)
{
    if(!hidden) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        static int nr = 0;
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

void ButtonTex::SetHighlight(bool state)
{
    highlight = state;
}

void ButtonTex::SetHighlightColor(SDL_Color color)
{
    prop.highlightColor = color;
}

void ButtonTex::SetTex(SDL_Texture *tex)
{
    this->prop.normal.tex = tex;
}

void ButtonTex::SetHighlightTex(SDL_Texture *tex)
{
    this->prop.over.tex = tex;
}

void ButtonTex::SetDrawBorder(bool border)
{
    prop.drawBorder = border;
}

ButtonTexProp ButtonTex::LoadButtonTexProp(Configuration *conf)
{
    int dim[4];
    Root::ParseDim(dim, conf);

    SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};

    Root *root = &Root::GetInstance();
    
    SDL_Color borderColor = {0, 0, 0, 255};
    bool drawBorder = true;
    if(conf->Get("border") == "")
        drawBorder = false;
    else
        borderColor = Widget::ParseVar("border", conf, root->GetVars());

    SDL_Color highlightColor = Widget::ParseVar("highlight", conf, root->GetVars());

    ButtonTexProp prop;
    if(conf->Get("over_tex_name") == "") {
        prop = {
                {root->GetScene(conf->Get("scene"))->GetTex(conf->Get("tex_name")), dimr},
                {},
                borderColor,
                highlightColor,
                drawBorder
            };
    } else {
        prop = {
                {root->GetScene(conf->Get("scene"))->GetTex(conf->Get("tex_name")), dimr},
                {root->GetScene(conf->Get("scene"))->GetTex(conf->Get("over_tex_name")), dimr},
                borderColor,
                highlightColor,
                drawBorder
            };
    }

    return prop;
}
