#pragma once

#include "Widget.h"
#include "../Text.h"


namespace PaceLib
{

    class Tooltip : public Widget
    {
        public:
            ~Tooltip();

            static void Create(WidgetId wid, SDL_Color color, Align align={V::MID, H::MID});
            static void Create(WidgetId wid, int w, int h, SDL_Color color, Align align={V::MID, H::MID});

            void Draw();

            void Add(Shape *s);

            void Update(SDL_Event *e);

        private:
            Tooltip(WidgetId wid, SDL_Rect shape, SDL_Color color);
    };



    class DefaultTooltip : public Widget
    {
        public:
            static void Create(WidgetId wid, PropFontText fto, SDL_Color color);
            static void Create(WidgetId wid, std::string text);

            void Draw();
        private:
            Text *to;

            DefaultTooltip(WidgetId wid, PropFontText fto, SDL_Color color);
    };

}