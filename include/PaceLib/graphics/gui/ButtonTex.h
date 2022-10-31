#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.hpp"
#include <functional>


namespace PaceLib
{

    class ButtonTex : public Widget
    {
        public:

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "scene" : "Default",
                "dim" : ["W_47%", "H_16%", "H_5%", "H_5%"],
                "tex_name" : "sn_yellow.png",
                "over_tex_name" : ""
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the buttontex will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic

            static void Begin(ShapeId sid, TexProp normal);
            static void Begin(ShapeId sid, TexProp normal, TexProp over);

//end static methods

            ButtonTex(ShapeId sid, TexProp normal, TexProp over);

            void SetTex(SDL_Texture *tex);

            void SetHighlightTex(SDL_Texture *tex);

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            void Draw();

            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

            ~ButtonTex();

        private:
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            TexProp normal;
            TexProp over;
    };

}