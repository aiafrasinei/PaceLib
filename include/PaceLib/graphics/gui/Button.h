#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.h"
#include <functional>


namespace PaceLib
{

    class Button : public Widget
    {
        public:

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_2%", "H_10%", "W_7.5%", "H_3%"],
                "color" : [40, 40, 40, 255],
                "scene" : "Default",
                "font" : "default",
                "text" : "Back",
                "text_color" : [140, 170, 140, 255],
                "align" : ["mid", "mid"]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

// programmatic
            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto, Align align={V::MID, H::MID});

//end static methods

            Button(ShapeId sid, PropDimColor dco, PropFontText fto, Align align);

            ~Button();


            void SetFont(FC_Font *font);

            void SetText(std::string text); 

            void SetTextAlign(Align align);

            void SetTextColor(SDL_Color color);

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            int GetTextSize();

            std::string GetText();


            void Draw();
            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

        private:
            Text *to;

            SDL_Color textColor;

            Align align;
            
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            SDL_Texture *tex;

            void InternalAlign(Align align);
    };

}