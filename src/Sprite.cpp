#include "Sprite.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

Sprite::Sprite(ShapeId sid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr)
{
    this->tex = tex;

    if(sid.parent->name == "root") {
        dest_rect.x = dim.x;
        dest_rect.y = dim.y;
    } else {
        dest_rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dim.x;
        dest_rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dim.y;
    }

    dest_rect.w = dim.w;
    dest_rect.h = dim.h;

    hidden = false;
    
    this->name = sid.name;

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

void Sprite::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);
    
        SDL_Texture *tex = Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetTex(conf->Get("tex_name").get<std::string>());

        sid.parent->Add(new Sprite(sid, tex, {dim[0], dim[1], dim[2], dim[3]}, conf->Get("offset").get<int>(), conf->Get("nr").get<int>()));
    }
}

void Sprite::Begin(std::string name, bool hasChildren)
{
    Root *root = &Root::GetInstance();
    Sprite::Begin({root->GetCurrent(), name});
    if (hasChildren) {
        Shape *prevParent = root->GetCurrent();
        root->SetCurrent(root->GetCurrent()->Get(name));
        root->GetCurrent()->SetParent(prevParent);
    }
}

void Sprite::End()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Sprite::Begin(ShapeId sid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr)
{
    sid.parent->Add(new Sprite(sid, tex, dim, offset, nr));
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
