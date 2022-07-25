#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Sprite : public Shape
    {
    public:
        
        /* Loads wconf file
        example format:
        {
            "dim" : ["H_82%", "H_11%", "H_32%", "H_32%"],
            "scene" : "Default",
            "tex_name" : "sprite_sheet.png",
            "offset" : 300,
            "nr" : 5
        }*/
        static void Create(WidgetId wid);
        static void Create(std::string);
        
        static void Create(WidgetId wid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr);

        void SetTex(SDL_Texture *tex);
        void SetRect(SDL_Rect dim);

        void Draw();

        ~Sprite();
        
    protected:         

    private:
        SDL_Texture *tex;

        SDL_Rect src_rect;
        SDL_Rect dest_rect;

        int offset;
        int nr;

        Sprite(WidgetId wid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr);
    };

}
