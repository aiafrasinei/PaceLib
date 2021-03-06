#include "ButtonTex.h"
#include "Window.h"
#include <functional>
#include "Root.h"


using namespace PaceLib;

ButtonTex::ButtonTex(WidgetId wid, PropTex normal, PropTex over)
{
    if(wid.parent->name == "root") {
        rect.x = normal.rect.x;
        rect.y = normal.rect.y;
    } else {
        rect.x = wid.parent->GetRect().x + normal.rect.x;
        rect.y = wid.parent->GetRect().y + normal.rect.y;
    }
    
    rect.w = normal.rect.w;
    rect.h = normal.rect.h;

    hidden = false;

    this->normal = {normal.tex, normal.rect};

    this->over = {over.tex, over.rect};

    this->name = wid.name;

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

void ButtonTex::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);
        std::string scene_name = conf->Get("scene").get<std::string>();

        ButtonTex *btex = nullptr;
        if(conf->Get("over_tex_name").get<std::string>() == "") {
            PropTex nullp = {nullptr, {0,0,0,255}};
            btex = new ButtonTex( wid, 
                {Root::GetInstance().GetScene(scene_name).GetTex(conf->Get("tex_name")), {dim[0], dim[1], dim[2], dim[3]}},
                nullp);
        } else {
            btex = new ButtonTex( wid, 
                {Root::GetInstance().GetScene(scene_name).GetTex(conf->Get("tex_name")), {dim[0], dim[1], dim[2], dim[3]}},
                {Root::GetInstance().GetScene(scene_name).GetTex(conf->Get("over_tex_name")), {dim[0], dim[1], dim[2], dim[3]}});
        }

        btex->conf = conf;
        if(btex != nullptr) {
            wid.parent->Add(btex);
        }
    }
}

void ButtonTex::Create(WidgetId wid, PropTex normal)
{
    PropTex nullp = {nullptr, {0,0,0,255}};
    wid.parent->Add(new ButtonTex(wid, normal, nullp));
}

void ButtonTex::Create(WidgetId wid, PropTex normal, PropTex over)
{
    wid.parent->Add(new ButtonTex(wid, normal, over));
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