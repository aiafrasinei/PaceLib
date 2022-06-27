#include "TexContainer.h"
#include "Window.h"

using namespace PaceLib;


TexContainer::TexContainer(std::string name, SDL_Renderer* renderer)
{
    this->name = name;
    this->renderer = renderer;
}

TexContainer::~TexContainer()
{
    for(int i=0; i<texs_rectangles.size(); i++) {
        delete texs_rectangles[i];
    }
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
    SDL_Texture* texture = load_texture(renderer, file_path.c_str());
    if(texture == NULL) {
		return false;
    }
    texs.push_back(texture);
    texs_names.push_back(file_path.filename());
    SDL_Rect *r = new SDL_Rect;
    texs_rectangles.push_back(r);

    return true;
}

bool TexContainer::Add(std::string name, SDL_Texture *tex)
{
    if(tex == NULL) {
		return false;
    }
    texs.push_back(tex);
    texs_names.push_back(name);
    SDL_Rect *r = new SDL_Rect;
    texs_rectangles.push_back(r);

    return true;
}

bool TexContainer::Add(std::filesystem::path file_path, int x, int y, int w , int h)
{
    int ret = Add(file_path);
    SetRect(file_path.filename(), x, y, w, h);

    return ret;
}

void TexContainer::SetRect(long index, int x, int y, int w , int h)
{
    texs_rectangles[index]->x = x;
    texs_rectangles[index]->y = y;
    texs_rectangles[index]->w = w;
    texs_rectangles[index]->h = h;
}

void TexContainer::SetRect(std::string name, int x, int y, int w , int h)
{
    for(int i=0; i<texs_names.size(); i++) {
        if(texs_names[i] == name) {
            texs_rectangles[i]->x = x;
            texs_rectangles[i]->y = y;
            texs_rectangles[i]->w = w;
            texs_rectangles[i]->h = h;
        }
    }
}

SDL_Rect *TexContainer::GetRect(long index)
{
    return texs_rectangles[index];
}

SDL_Rect *TexContainer::GetRect(std::string name)
{
    for(int i=0; i<texs_names.size(); i++) {
        if(texs_names[i] == name) {
            return texs_rectangles[i];
        }
    }

    return NULL;
}

SDL_Texture *TexContainer::Get(long index)
{
    return texs[index];
}

SDL_Texture *TexContainer::Get(std::string name)
{
    for(int i=0; i<texs_names.size(); i++) {
        if(texs_names[i] == name) {
            return texs[i];
        }        
    }
    
    return NULL;
}

std::vector<SDL_Texture *> TexContainer::GetTexs()
{
    return texs;
}

long TexContainer::GetNrTexs()
{
    return texs.size();
}

bool TexContainer::Remove(long index)
{
    if(index >= texs.size()) {
        return false;
    }

    SDL_DestroyTexture(texs[index]);
    texs.erase(texs.begin() + index);
    texs_names.erase(texs_names.begin() + index);

    return true;
}

bool TexContainer::Remove(std::string name)
{    
    bool found = false;
    for(int i=0; i<texs_names.size(); i++) {
        if(texs_names[i] == name) {
            found = true;

            SDL_DestroyTexture(texs[i]);
            texs.erase(texs.begin() + i);
            texs_names.erase(texs_names.begin() + i);
            break;
        }
    }    

    return found;
}
