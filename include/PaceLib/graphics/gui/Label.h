#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "../Text.h"


namespace PaceLib
{

    class Label : public Widget
    {
        public:
            ~Label();

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_0.5%", "W_0.5%", "W_7.5%", "H_3%"],
                "color" : "parent",
                "scene" : "Default",
                "font" : "default",
                "text" : "Main Menu",
                "text_color" : [0, 0, 0, 255],
                "align" : ["mid", "mid"]
            }*/
            static void Create(WidgetId wid);

            static void Create(WidgetId wid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID});
            static void Create(WidgetId wid, SDL_Rect dim, std::string text);

            void SetTextAlign(Align align);

            void SetTextColor(SDL_Color color);

            void Draw();

        private:
            Text *to;

            SDL_Color textColor;

            Align align;

            Label(WidgetId wid, PropDimColor dmo, PropFontText fto, Align align);

            void InternalAlign(Align align);
    };

}