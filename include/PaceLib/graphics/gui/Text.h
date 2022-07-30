#pragma once

#include "Widget.h"
#include "../utils/SDL2/SDL_FontCache.h"


namespace PaceLib
{

    class Text : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "text" : "Text text text",
            "scene" : "Default",
            "font" : "default",
            "pos" : ["W_0.6%", "W_0.6%"],
            "text_color" : [140, 140, 140, 255]
        }*/
        static void Create(ShapeId wid);
        static void Begin(std::string name, bool hasChildren=false);
        static void End();

        static void Create(ShapeId wid, PropFontText fto, int x, int y, SDL_Color color);
        static void Create(ShapeId wid, int x, int y, SDL_Color color, std::string text);
        static Text *Create(FC_Font *font, std::string text, int x, int y, SDL_Color color);

        void Draw();

        int GetWidth();
        int GetHeight();

        void SetX(int x);
        void SetY(int y);

        std::string GetText();
        void SetText(std::string text);

        void SetTextColor(SDL_Color color);

        ~Text();
        
    protected:         

    private:
        FC_Font *font;
        std::string text;

        int x,y;
        SDL_Rect rect;

        Text(ShapeId wid, PropFontText fto, int x, int y, SDL_Color color);
        Text(FC_Font *font, int x, int y, SDL_Color color, std::string text);
    };

}
