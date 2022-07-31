#pragma once

#include "Widget.h"
#include "Button.h"
#include "Tab.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"


namespace PaceLib
{

    class Tabber : public Widget
    {
        public:

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_3%", "W_30%", "W_19%", "W_19%"],
                "color" : [70, 80, 70, 255],
                "scene" : "Default",
                "font" : "default",
                "text" : ""
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

// programmatic

            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto);

//end static methods

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void Draw();

            void AddTab(std::string text);
            void AddTab(std::string name, std::string text);

            void Update(SDL_Event *e);

            Tab *GetTab(int index);

            static unsigned int current;

            ~Tabber();
            
        private:
            std::vector<std::string> titles;

            std::vector<Button *> buttons;
            std::vector<Tab *> tabs;

            SDL_Color textColor;

            int xb;

            int bcounter;

            SDL_Rect top;

            Tabber(ShapeId sid, PropDimColor dmo, PropFontText fto);
    };

}