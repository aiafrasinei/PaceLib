#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "../../core/interfaces/Focusable.h"
#include "Text.h"


namespace PaceLib
{

    class TextInput : public Widget, public Focusable
    {
        public:

//static methods

// json configuration
            /* Loads wconf file
            example format:
            }
                "dim" : ["W_1%", "H_28%", "W_7.5%", "H_3%"],
                "color" : [120, 120, 120, 255],
                "scene" : "Default",
                "font" : "default",
                "text" : ""
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the textinput will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programatic
            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto);

//end static methods

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void Draw();

            void Update(SDL_Event *e);

            std::string GetText();
            
            ~TextInput();
        private:
            Text *to;

            SDL_Color textColor;

            TextInput(ShapeId sid, PropDimColor dmo, PropFontText fto);
    };

}