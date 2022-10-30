#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.hpp"
#include <functional>


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
                "scene" : "Default",
                "dim" : ["H_82%", "H_11%", "W_7.5%", "H_3%"],
                "font" : "default",
                "text" : "Start",
                "text_color" : "$TEXT",
                "align" : "mid",
                "background" : "$BACKGROUND",
                "border" : "$BORDER",
                "highlight" : "$HIGHLIGHT"
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the button will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic
            static void Begin(ShapeId sid, LabelProp prop);

//end static methods

            void SetText(std::string text);
            std::string GetText();
            void SetTextAlign(HorizontalAlign align);

            int GetTextSize();

            LabelProp GetProp();
   
            void Draw();

            Label();

            ~Label();

        protected:
            LabelProp prop;

            int textSize;

            void InternalInit();

            static LabelProp LoadLabelProp(Configuration *conf);

            Label(ShapeId sid, LabelProp prop);
    };

}