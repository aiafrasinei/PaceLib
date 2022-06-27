#pragma once

#include <string>
#include <vector>
#include "TexContainer.h"
#include "FontContainer.h"
#include "utils/sdlu.h"
#include "core/interfaces/Drawable.h"


namespace PaceLib
{

    class Scene : public Drawable
    {
    public:
        Scene(std::string name, SDL_Window* window, SDL_Renderer* renderer);    
        ~Scene();
        
        void Start();
        void Draw();
        void Stop();

        std::string GetName();
        void SetName(std::string name);

        PaceLib::TexContainer *GetTexContainer();
        PaceLib::FontContainer *GetFontContainer();

        bool AddTex(std::filesystem::path file_path, int x, int y, int w, int h);
        bool AddFont(std::string name, std::filesystem::path file_path, int size, int r, int g, int b, int a);

        SDL_Texture *GetTex(int index);
        SDL_Texture *GetTex(std::string name);

        FC_Font *GetFont(int index);
        FC_Font *GetFont(std::string name);

        void Update(SDL_Event *event);

    protected:

    private:
        PaceLib::TexContainer *tex_atlas;
        PaceLib::FontContainer *font_atlas;

        SDL_Window* window;
        SDL_Renderer* renderer;

        std::string name;
    };

}
