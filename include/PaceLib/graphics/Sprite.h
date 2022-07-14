#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Sprite : public Shape
    {
    public:
        
        ~Sprite();

        static void Create(std::string name, Shape *parent, SDL_Texture *tex, SDL_Rect dim, int offset, int nr);

        void SetTex(SDL_Texture *tex);
        void SetRect(SDL_Rect dim);

        void Draw();
    protected:         

    private:
        SDL_Texture *tex;

        SDL_Rect src_rect;
        SDL_Rect dest_rect;

        int offset;
        int nr;

        Sprite(std::string name, SDL_Texture *tex, SDL_Rect dim, int offset, int nr);
    };

}
