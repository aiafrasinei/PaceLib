#include "TexContainer.hpp"
#include "Window.hpp"


using namespace PaceLib;


TexContainer::TexContainer(std::string name, SDL_Renderer* renderer)
{
    this->name = name;
    this->renderer = renderer;
}

TexContainer::~TexContainer()
{
    for (auto const& pair : ntr) {
        SDL_DestroyTexture(pair.second->tex);
    }
    ntr.clear();
}

std::string TexContainer::GetName()
{
    return name;
}

void TexContainer::ChangeName(std::string name)
{
    this->name = name;
}

bool TexContainer::Add(std::filesystem::path file_path)
{
    SDL_Texture* tex = load_texture(renderer, file_path.c_str());
    if(tex == NULL) {
		return false;
    }

    SDL_Rect *r = new SDL_Rect;

    PropTex *pt = new PropTex();
    pt->tex = tex;
    pt->rect = *r;
    ntr[file_path.filename()] = pt;

    return true;
}

bool TexContainer::Add(std::string name, SDL_Texture *tex)
{
    if(tex == NULL) {
		return false;
    }

    SDL_Rect *r = new SDL_Rect;

    PropTex *pt = new PropTex();
    pt->tex = tex;
    pt->rect = *r;
    ntr[name] = pt;

    return true;
}

bool TexContainer::Add(std::filesystem::path file_path, int x, int y, int w , int h)
{
    int ret = Add(file_path);
    SetRect(file_path.filename(), x, y, w, h);

    return ret;
}

void TexContainer::SetRect(std::string name, int x, int y, int w , int h)
{
    ntr[name]->rect.x = x;
    ntr[name]->rect.y = y;
    ntr[name]->rect.w = w;
    ntr[name]->rect.h = h;
}

SDL_Rect *TexContainer::GetRect(std::string name)
{
    return &ntr[name]->rect;
}

SDL_Texture *TexContainer::Get(std::string name)
{
    return ntr[name]->tex;
}

long TexContainer::GetNrTexs()
{
    return ntr.size();
}

void TexContainer::Remove(std::string name)
{    
    SDL_DestroyTexture(ntr[name]->tex);
    ntr.erase(name);
}
