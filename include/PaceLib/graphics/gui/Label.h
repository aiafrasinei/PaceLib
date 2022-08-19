#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"


namespace PaceLib
{

    class Label : public Widget
    {
        public:

//static methods

// json configuration
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
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the label will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic
            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID});

//end static methods

            void SetTextAlign(Align align);

            void SetTextColor(SDL_Color color);

            SDL_Color GetTextColor();

            void Draw();

            ~Label();

        private:
            SDL_Color textColor;

            Align align;

            PropFontText fto;

            Label(ShapeId sid, PropDimColor dmo, PropFontText fto, Align align);

            void InternalInit();
    };

}