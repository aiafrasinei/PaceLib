#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Tex : public Hidable
    {
    public:
        Tex(std::string path, int x, int y);
        Tex(std::string path, int x, int y, int w, int h);
        
        Tex(SDL_Texture *tex, int x, int y);
        Tex(SDL_Texture *tex, int x, int y, int w, int h);

        ~Tex();

        void Free();
        
        void Draw(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void SetColor(Uint8 r, Uint8 g, Uint8 b);
        void SetBlendMode(SDL_BlendMode blending);
        void SetAlpha(Uint8 a);

        int GetWidth();
        int GetHeight();
    protected:

    private:
        SDL_Texture *tex;
        SDL_Rect rect;
    };

}
