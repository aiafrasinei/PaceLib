#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Sprite : public Shape
    {
    public:

//static methods

// json configuration

        /* Loads wconf file
        example format:
        {
            "dim" : ["H_82%", "H_11%", "H_32%", "H_32%"],
            "scene" : "Default",
            "tex_name" : "sprite_sheet.png",
            "offset" : 300,
            "nr" : 5
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string, bool hasChildren=false);
        static void End();

// programmatic

        static void Begin(ShapeId sid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr);

//end static methods

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

        Sprite(ShapeId sid, SDL_Texture *tex, SDL_Rect dim, int offset, int nr);
    };

}
