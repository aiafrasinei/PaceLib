#include "Scene.h"

using namespace PaceLib;


Scene::Scene(std::string name, SDL_Window* window, SDL_Renderer* renderer)
{
    this->name = name;

    this->window = window;
    this->renderer = renderer; 

    tex_atlas = new TexContainer(name, renderer);
    font_atlas = new FontContainer(name);
}

Scene::~Scene()
{
    
}

void Scene::SetName(std::string name)
{
    this->name = name;
}

TexContainer *Scene::GetTexContainer()
{
    return tex_atlas;
}

FontContainer *Scene::GetFontContainer()
{
    return font_atlas;
}


bool Scene::AddTex(std::filesystem::path file_path, int x, int y, int w, int h)
{
    tex_atlas->Add(file_path, x, y, w, h);
    return true;
}

bool Scene::AddFont(std::string name, std::filesystem::path file_path, int size, int r, int g, int b, int a)
{
    return font_atlas->Add(name, file_path, size, r, g, b, a);
}

SDL_Texture *Scene::GetTex(std::string name)
{
    return tex_atlas->Get(name);
}

FC_Font *Scene::GetFont(int index)
{
    return font_atlas->Get(index);
}

FC_Font *Scene::GetFont(std::string name)
{
    return font_atlas->Get(name);
}

void Scene::Start()
{

}

void Scene::Draw()
{
    SDL_RenderCopy(renderer, tex_atlas->Get(0), NULL, tex_atlas->GetRect(0));
}

void Scene::Stop()
{

}

void Scene::Update(SDL_Event *e)
{
    if((*e).type == SDL_KEYDOWN)
    { 
        switch((*e).key.keysym.sym)
        {
            case SDLK_LEFT:
                //if(current_tex_index>0)
                 //   current_tex_index--;
                break;                
            case SDLK_RIGHT:
                //if(current_tex_index<tex_counter)
                //    current_tex_index++;
                break;   

            default:	
                break;
        }
    }
}

std::string Scene::GetName()
{
    return name;
}