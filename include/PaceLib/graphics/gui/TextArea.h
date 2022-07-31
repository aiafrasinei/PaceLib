#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"


namespace PaceLib
{

    class TextArea : public Widget
    {
        public:
            ~TextArea();

//static methods

// json configuration
            static void Begin(ShapeId sid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

// programatic
            static void Begin(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align={V::MID, H::MID});

//end static methods

            void SetTextAlign(Align align);

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void SetTextSpacing(int size);

            void Draw();

        private:
            std::vector<Text *> tos;

            SDL_Color textColor;

            Align align;

            int textSpacing;

            TextArea(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align);

            void InternalAlign(Align align);
    };

}