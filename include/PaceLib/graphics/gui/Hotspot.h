#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.h"
#include <functional>


namespace PaceLib
{

    enum class Hover
    {
        RECT,
        FILLED,
        TEXTURE
    };

    class Hotspot : public Widget
    {
        public:
            ~Hotspot();

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_25%", "W_3%", "W_20%", "W_22%"],
                "color" : [80, 70, 80, 255]
            }*/
            static void Create(ShapeId sid);
            static void Create(std::string name);
            
            static void Create(ShapeId sid, PropDimColor dco, Hover type=Hover::RECT, SDL_Texture *tex=nullptr);

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            void SetRec(SDL_Rect rect);

            void Draw();

            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

        private:
            Hotspot(ShapeId sid, PropDimColor dco, Hover type=Hover::RECT, SDL_Texture *tex=nullptr);

            bool mouseOver;

            bool isHighlight;

            Hover type;

            SDL_Color highlight;

            SDL_Texture *tex;
    };

}