#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.hpp"
#include <functional>


namespace PaceLib
{

    class CheckBox : public Widget
    {
        public:
            ~CheckBox();

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_1%", "W_19%", "H_2.3%", "H_2.3%"],
                "color" : [120, 120, 120, 255],
                "scene" : "Default",
                "font" : "default",
                "text" : "CheckBox",
                "text_color" : [0, 0, 0, 255]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the checkbox will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic
            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto, SDL_Color textColor);
            static void Begin(ShapeId sid, PropTex pto);

//end static methods

            CheckBox(ShapeId sid, PropDimColor dco, PropFontText fto, SDL_Color textColor);
            CheckBox(ShapeId sid, PropTex pto);

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            void SetTextColor(SDL_Color color);

            void Draw();

            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

            bool IsChecked();

            SDL_Color GetTextColor();

        private:
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            bool checked;

            SDL_Texture *tex;

            Text *to;

            SDL_Color textColor;

            SDL_Rect midrect;

            PropFontText fto;

            int textSize;

            void InternalInit();
    };

}