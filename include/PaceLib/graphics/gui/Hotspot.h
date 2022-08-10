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

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_25%", "W_3%", "W_20%", "W_22%"],
                "color" : [80, 70, 80, 255]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the hotspot will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic

            static void Begin(ShapeId sid, PropDimColor dco, Hover type=Hover::RECT, SDL_Texture *tex=nullptr);

//end static methods

            void SetHighlight(bool state);
            
            void SetHighlightColor(SDL_Color color);

            void SetRec(SDL_Rect rect);

            void Draw();

            void Update(SDL_Event *e);

            std::function<void(void)> onClickCallback;

            ~Hotspot();

        private:
            Hotspot(ShapeId sid, PropDimColor dco, Hover type=Hover::RECT, SDL_Texture *tex=nullptr);

            bool mouseOver;

            bool isHighlight;

            Hover type;

            SDL_Color highlight;

            SDL_Texture *tex;
    };

}