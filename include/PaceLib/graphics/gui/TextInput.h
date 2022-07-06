#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "../../core/interfaces/Focusable.h"
#include "../Text.h"


namespace PaceLib
{

    class TextInput : public Widget, public Focusable
    {
        public:
            ~TextInput();

            /* Loads wconf file
            example format:
            }
                "dim" : ["W_1%", "H_28%", "W_7.5%", "H_3%"],
                "color" : [120, 120, 120, 255],
                "scene" : "Default",
                "font" : "default",
                "text" : ""
            }*/
            static void Create(WidgetId wid);

            static void Create(WidgetId wid, PropDimColor dco, PropFontText fto);

            static void Create(WidgetId wid, SDL_Rect dim, std::string text);

            static void Create(WidgetId wid, SDL_Rect dim);

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void Draw();

            void Update(SDL_Event *e);

            std::string GetText();
            
        private:
            Text *to;

            SDL_Color textColor;

            TextInput(WidgetId wid, PropDimColor dmo, PropFontText fto);
    };

}