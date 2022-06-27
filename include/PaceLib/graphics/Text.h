#pragma once

#include "Widget.h"
#include "../utils/SDL2/SDL_FontCache.h"


namespace PaceLib
{

    class Text : public Shape
    {
    public:
        ~Text();

        static void Create(WidgetId wid);
        static void Create(WidgetId wid, PropFontText fto, float x, float y, SDL_Color color);
        static void Create(WidgetId wid, float x, float y, SDL_Color color, std::string text);
        static Text *Create(FC_Font *font, std::string text, float x, float y, SDL_Color color);

        void Draw();

        float GetWidth();
        float GetHeight();

        void SetX(float x);
        void SetY(float y);

        std::string GetText();
        void SetText(std::string text);

        void SetTextColor(SDL_Color color);
    protected:         

    private:
        FC_Font *font;
        std::string text;

        float x,y;
        SDL_Rect rect;

        Text(WidgetId wid, PropFontText fto, float x, float y, SDL_Color color);
        Text(FC_Font *font, float x, float y, SDL_Color color, std::string text);
    };

}
