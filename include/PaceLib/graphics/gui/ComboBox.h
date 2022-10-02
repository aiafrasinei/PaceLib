#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.hpp"
#include <functional>


namespace PaceLib
{

    class ComboBox : public Widget
    {
        public:

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {

            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the button will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic
            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto);

            ~ComboBox();

            std::function<void(void)> onClickCallback;
            
        private:
            ComboBox(ShapeId sid, PropDimColor dco, PropFontText fto);

            SDL_Color textColor;

            Align align;
            
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            SDL_Texture *tex;

            std::string text;

            int textSize;

            PropFontText fto;
    };
}