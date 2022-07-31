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
            ~Tabber();

            //TODO
            static void Create(ShapeId sid);
            static void Create(std::string name);

            static void Create(ShapeId sid, PropDimColor dco, PropFontText fto);

            static void Create(ShapeId sid, PropDimColor dco);

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void Draw();

            void AddTab(std::string text);
            void AddTab(std::string name, std::string text);

            void Update(SDL_Event *e);

            Tab *GetTab(int index);

            static unsigned int current;

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