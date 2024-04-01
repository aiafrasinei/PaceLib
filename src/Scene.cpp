#include "Scene.hpp"

using namespace PaceLib;

Scene::Scene(std::string name, SDL_Window *window, SDL_Renderer *renderer) {
  this->name = name;

  this->window = window;
  this->renderer = renderer;

  tex_atlas = new TexContainer(name, renderer);
  font_atlas = new TexContainer(name, renderer);
  ttf_atlas = new TtfContainer(name);
}

Scene::~Scene() {
  delete font_atlas;
  delete tex_atlas;
  delete ttf_atlas;
}

void Scene::SetName(std::string name) { this->name = name; }

TexContainer *Scene::GetTexContainer() { return tex_atlas; }

TexContainer *Scene::GetFontContainer() { return font_atlas; }

TtfContainer *Scene::GetTtfContainer() { return ttf_atlas; }

bool Scene::AddTex(std::filesystem::path file_path, int x, int y, int w,
                   int h) {
  return tex_atlas->Add(file_path, x, y, w, h);
}

bool Scene::AddFont(std::string name, std::string font, std::string text, SDL_Color color) {
  SDL_Surface* surface = TTF_RenderText_Solid(GetTtfContainer()->Get(font), text.c_str(), color);
  SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
  font_atlas->Add(name, tex);

  return true;
}

bool Scene::AddTtf(std::string name, std::filesystem::path file_path, int size, int style, int outline) {
  return ttf_atlas->Add(name, file_path, size, style, outline);
}

SDL_Texture *Scene::GetTex(std::string name) { return tex_atlas->Get(name); }

SDL_Texture *Scene::GetFont(std::string name) { return font_atlas->Get(name); }

TTF_Font *Scene::GetTtf(std::string name) { return ttf_atlas->Get(name); }

void Scene::Start() {}

void Scene::Draw() {
  // SDL_RenderCopy(renderer, tex_atlas->Get(0), NULL, tex_atlas->GetRect(0));
}

void Scene::Stop() {}

void Scene::Update(SDL_Event *e) {
  if ((*e).type == SDL_KEYDOWN) {
    switch ((*e).key.keysym.sym) {
    case SDLK_LEFT:
      // if(current_tex_index>0)
      //    current_tex_index--;
      break;
    case SDLK_RIGHT:
      // if(current_tex_index<tex_counter)
      //     current_tex_index++;
      break;

    default:
      break;
    }
  }
}

std::string Scene::GetName() { return name; }