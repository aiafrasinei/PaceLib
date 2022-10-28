#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.hpp"
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
                "scene" : "Default",
                "dim" : ["W_2%", "H_10%", "W_7.5%", "H_3%"],
                "background_color" : [40, 40, 40, 255],
                "highlight_color" : [30, 30, 30, 255],
                "border_color" : [0, 0, 0, 255],
                "font" : "default",
                "text" : "Back",
                "text_color" : [140, 170, 140, 255],
                "align" : ["mid", "mid"]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the button will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic
            static void Begin(ShapeId sid, ButtonProp prop);

//end static methods

            ~Button();

            void SetText(std::string text); 

            std::string GetText();

            int GetTextSize();

            void SetHighlight(bool state);

            ButtonProp GetProp();

            void Draw();
            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

        private:

            ButtonProp prop;

            bool mouseOver;

            bool highlight;

            int textSize;

            void InternalInit();

            Button(ShapeId sid, ButtonProp prop);
    };

}