#include "ButtonTex.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

ButtonTex::ButtonTex(ShapeId sid, PropTex normal, PropTex over)
{
    if(sid.parent->name == "root") {
        rect.x = normal.rect.x;
        rect.y = normal.rect.y;
    } else {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + normal.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + normal.rect.y;
    }
    
    rect.w = normal.rect.w;
    rect.h = normal.rect.h;

    hidden = false;

    this->normal = {normal.tex, normal.rect};

    this->over = {over.tex, over.rect};

    this->name = sid.name;

    mouseOver = false;

    highlight = true;

    Uint8 hr = color.r + 30;
    Uint8 hg = color.g + 30;
    Uint8 hb = color.b + 30;
    Uint8 ha = 255;
    highlightColor = { hr , hg , hb, ha };

    wtype = WidgetType::BUTTONTEX;
}

ButtonTex::~ButtonTex()
{

}

void ButtonTex::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);
        std::string scene_name = conf->Get("scene").get<std::string>();

        ButtonTex *btex = nullptr;
        if(conf->Get("over_tex_name").get<std::string>() == "") {
            PropTex nullp = {nullptr, {0,0,0,255}};
            btex = new ButtonTex( sid, 
                {Root::GetInstance().GetScene(scene_name).GetTex(conf->Get("tex_name")), {dim[0], dim[1], dim[2], dim[3]}},
                nullp);
        } else {
            btex = new ButtonTex( sid, 
                {Root::GetInstance().GetScene(scene_name).GetTex(conf->Get("tex_name")), {dim[0], dim[1], dim[2], dim[3]}},
                {Root::GetInstance().GetScene(scene_name).GetTex(conf->Get("over_tex_name")), {dim[0], dim[1], dim[2], dim[3]}});
        }

        btex->conf = conf;
        if(btex != nullptr) {
            sid.parent->Add(btex);
        }
    }
}

void ButtonTex::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    ButtonTex::Begin({(Widget *)root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->Get(root->GetCurrent()->name)->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }
}

void ButtonTex::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void ButtonTex::Begin(ShapeId sid, PropTex normal)
{
    PropTex nullp = {nullptr, {0,0,0,255}};
    sid.parent->Add(new ButtonTex(sid, normal, nullp));
}

void ButtonTex::Begin(ShapeId sid, PropTex normal, PropTex over)
{
    sid.parent->Add(new ButtonTex(sid, normal, over));
}

void ButtonTex::Draw()
{
    if(!hidden) {
        if(mouseOver) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
            if(over.tex == nullptr) {
                SDL_SetTextureColorMod( normal.tex, highlightColor.r, highlightColor.g, highlightColor.b );
            }
        } else {
            SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        }

        SDL_RenderCopy(Window::GetRenderer(), normal.tex, NULL, &normal.rect);
        if(over.tex == nullptr) {
            SDL_SetTextureColorMod(normal.tex, 255, 255, 255);
        }

        if(mouseOver) {
            if(over.tex != nullptr) {
                SDL_RenderCopy(Window::GetRenderer(), over.tex, NULL, &over.rect);
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
    highlightColor.r = color.r;
    highlightColor.g = color.g;
    highlightColor.b = color.b;
    highlightColor.a = color.a;
}

void ButtonTex::SetTex(SDL_Texture *tex)
{
    this->normal.tex = tex;
}

void ButtonTex::SetHighlightTex(SDL_Texture *tex)
{
    this->over.tex = tex;
}