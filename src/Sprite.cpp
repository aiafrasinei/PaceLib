#include "Sprite.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

Sprite::Sprite(WidgetId wid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr)
{
    this->tex = tex;

    if(wid.parent->name == "root") {
        dest_rect.x = dim.x;
        dest_rect.y = dim.y;
    } else {
        dest_rect.x = wid.parent->GetRect().x + dim.x;
        dest_rect.y = wid.parent->GetRect().y + dim.y;
    }

    dest_rect.w = dim.w;
    dest_rect.h = dim.h;

    hidden = false;
    
    this->name = wid.name;

    this->offset = offset;
    this->nr = nr;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = offset;
    src_rect.h = offset;

}

Sprite::~Sprite()
{

}

void Sprite::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);
    
        SDL_Texture *tex = Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetTex(conf->Get("tex_name").get<std::string>());

        wid.parent->Add(new Sprite(wid, tex, {dim[0], dim[1], dim[2], dim[3]}, conf->Get("offset").get<int>(), conf->Get("nr").get<int>()));
    }
}

void Sprite::Create(std::string name)
{
    Sprite::Create({&Root::GetInstance(), name});
}

void Sprite::Create(WidgetId wid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr)
{
    wid.parent->Add(new Sprite(wid, tex, dim, offset, nr));
}

void Sprite::Draw()
{
    if(!hidden) {
        SDL_RenderCopy(Window::GetRenderer(), tex, &src_rect, &dest_rect);
        src_rect.x = src_rect.x + offset;
        if(src_rect.x == nr*offset) {
            src_rect.x = 0;
        }
    }
}

void Sprite::SetTex(SDL_Texture *tex)
{
    this->tex = tex;
}

void Sprite::SetRect(SDL_Rect dim)
{
    dest_rect.x = dim.x;
    dest_rect.y = dim.y;
    dest_rect.w = dim.w;
    dest_rect.h = dim.h;
}
