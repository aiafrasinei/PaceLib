#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.h"
#include <functional>


namespace PaceLib
{

    class CheckBox : public Widget
    {
        public:
            ~CheckBox();

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
            static void Create(ShapeId wid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

            static void Create(ShapeId wid, PropDimColor dco, PropFontText fto, SDL_Color textColor);

            static void Create(ShapeId wid, PropDimColor dco, std::string text);

            static void Create(ShapeId wid, PropTex pto);

            CheckBox(ShapeId wid, PropDimColor dco, PropFontText fto, SDL_Color textColor);
            CheckBox(ShapeId wid, PropTex pto);

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            void SetTextColor(SDL_Color color);

            void Draw();

            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

            bool IsChecked();

        private:
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            bool checked;

            SDL_Texture *tex;

            Text *to;

            SDL_Color textColor;

            SDL_Rect midrect;
    };

}