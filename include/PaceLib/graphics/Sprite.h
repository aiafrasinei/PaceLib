#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Sprite : public Shape
    {
    public:
        
        ~Sprite();

        static void Create(std::string name, Shape *parent, SDL_Texture *tex, SDL_Rect shape);

        void SetTex(SDL_Texture *tex);
        void SetRect(float x, float y, float w , float h);

        void Draw();
    protected:         

    private:
        SDL_Texture *tex;
        SDL_Rect rect;

        Sprite(std::string name, SDL_Texture *tex, SDL_Rect shape);
    };

}
