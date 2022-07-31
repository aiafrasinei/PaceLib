#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.h"
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
                "dim" : ["W_47%", "H_16%", "H_5%", "H_5%"],
                "scene" : "Default",
                "tex_name" : "sn_yellow.png",
                "over_tex_name" : ""
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

// programmatic

            static void Begin(ShapeId sid, PropTex normal);
            static void Begin(ShapeId sid, PropTex normal, PropTex over);

//end static methods

            ButtonTex(ShapeId sid, PropTex normal, PropTex over);

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

            PropTex normal;
            PropTex over;
    };

}