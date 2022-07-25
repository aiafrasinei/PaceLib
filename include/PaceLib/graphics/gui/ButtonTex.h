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
            ~ButtonTex();

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_47%", "H_16%", "H_5%", "H_5%"],
                "scene" : "Default",
                "tex_name" : "sn_yellow.png",
                "over_tex_name" : ""
            }*/
            static void Create(WidgetId wid);
            static void Create(std::string name);

            static void Create(WidgetId wid, PropTex normal);

            static void Create(WidgetId wid, PropTex normal, PropTex over);

            ButtonTex(WidgetId wid, PropTex normal, PropTex over);

            void SetTex(SDL_Texture *tex);

            void SetHighlightTex(SDL_Texture *tex);

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            void Draw();

            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

        private:
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            PropTex normal;
            PropTex over;
    };

}