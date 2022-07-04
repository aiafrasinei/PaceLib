#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "../Text.h"
#include "../core/interfaces/Updateable.h"
#include <functional>


namespace PaceLib
{

    class CheckBox : public Widget
    {
        public:
            ~CheckBox();

            //TODO
            static void Create(WidgetId wid);

            static void Create(WidgetId wid, PropDimColor dco, PropFontText fto, SDL_Color textColor);

            static void Create(WidgetId wid, PropDimColor dco, std::string text);

            static void Create(WidgetId wid, PropTex pto);

            CheckBox(WidgetId wid, PropDimColor dco, PropFontText fto, SDL_Color textColor);
            CheckBox(WidgetId wid, PropTex pto);

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