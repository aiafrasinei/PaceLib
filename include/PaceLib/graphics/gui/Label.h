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

            //TODO
            static void Create(WidgetId wid);

            static void Create(WidgetId wid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID});
            static void Create(WidgetId wid, SDL_Rect dim, std::string text);

            void SetTextAlign(Align align);

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void Draw();

        private:
            Text *to;

            SDL_Color textColor;

            Align align;

            Label(WidgetId wid, PropDimColor dmo, PropFontText fto, Align align);

            void InternalAlign(Align align);
    };

}