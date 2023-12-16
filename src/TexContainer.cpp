#include "TexContainer.hpp"
#include "Window.hpp"
#include "utils/ConLog.hpp"

using namespace PaceLib;

TexContainer::TexContainer(std::string name, SDL_Renderer *renderer) {
  this->name = name;
  this->renderer = renderer;
}

TexContainer::~TexContainer() {
  for (auto pair : ntr) {
    SDL_DestroyTexture(pair.second->tex);
  }
  ntr.clear();
}

std::string TexContainer::GetName() { return name; }

void TexContainer::ChangeName(std::string name) { this->name = name; }

bool TexContainer::Add(std::filesystem::path file_path) {
  SDL_Texture *tex = LoadTexture(renderer, file_path.c_str());
  if (tex == nullptr) {
    return false;
  }

  TexProp *pt = new TexProp();
  pt->tex = tex;
  pt->rect = {0, 0, 0, 0};

  ntr[file_path.filename()] = pt;

  return true;
}

bool TexContainer::Add(std::string name, SDL_Texture *tex) {
  if (tex == nullptr) {
    return false;
  }

  TexProp *pt = new TexProp();
  pt->tex = tex;
  pt->rect = {0, 0, 0, 0};

  ntr[name] = pt;

  return true;
}

bool TexContainer::Add(std::filesystem::path file_path, int x, int y, int w,
                       int h) {
  int ret = Add(file_path);
  SetRect(file_path.filename(), x, y, w, h);

  return ret;
}

void TexContainer::SetRect(std::string name, int x, int y, int w, int h) {
  ntr[name]->rect.x = x;
  ntr[name]->rect.y = y;
  ntr[name]->rect.w = w;
  ntr[name]->rect.h = h;
}

SDL_Rect *TexContainer::GetRect(std::string name) { return &ntr[name]->rect; }

SDL_Texture *TexContainer::Get(std::string name) { return ntr[name]->tex; }

long TexContainer::GetNrTexs() { return ntr.size(); }

void TexContainer::Remove(std::string name) {
  SDL_DestroyTexture(ntr[name]->tex);
  ntr.erase(name);
}

SDL_Texture *TexContainer::LoadTexture(SDL_Renderer *renderer,
                                       std::string path) {
  SDL_Texture *new_tex = nullptr;

  SDL_Surface *loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == nullptr) {
    ConLog::Error("Unable to load image " + path +
                  "! SDL_image Error: " + IMG_GetError());
  } else {
    new_tex = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (new_tex == nullptr) {
      ConLog::Error("Unable to create texture from " + path +
                    "! SDL Error: " + SDL_GetError());
    } else {
      ConLog::Info("Loaded " + path);
    }

    SDL_FreeSurface(loaded_surface);
  }

  return new_tex;
}
