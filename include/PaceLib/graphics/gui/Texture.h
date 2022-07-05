#pragma once

#include "Widget.h"
#include "graphics/Tex.h"


namespace PaceLib
{

    class Texture : public Widget
    {
    public:
        ~Texture();
        
        /* Loads wconf file
        example format:
        {
            "tex_name": "tex.png",
            "dim" : [10, 10, 100 , 100]
        }*/
        static void Create(WidgetId wid);

        static void Create(WidgetId wid, SDL_Texture *tex, int x, int y);
        static void Create(WidgetId wid, SDL_Texture *tex, SDL_Rect dim);
        
        void Draw();

        void SetColor(Uint8 r, Uint8 g, Uint8 b);
        void SetBlendMode(SDL_BlendMode blending);
        void SetAlpha(Uint8 a);

        int GetWidth();
        int GetHeight();
    protected:

    private:
        SDL_Texture *tex;
        SDL_Rect rect;

        Tex *ctex;

        Texture(WidgetId wid, SDL_Texture *tex, SDL_Rect dim);
    };

}
