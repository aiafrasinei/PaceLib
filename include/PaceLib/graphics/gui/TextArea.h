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
            static void Begin(std::string name);

            //used when the textarea will have child elements
            static void BeginBlock(std::string name);
            static void End();

// programatic
            static void Begin(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align={V::MID, H::MID});

//end static methods

            void SetTextAlign(Align align);

            void SetTextColor(SDL_Color color);

            SDL_Color GetTextColor();

            void SetTextSpacing(int size);

            void Draw();

        private:
            SDL_Color textColor;

            Align align;

            int textSpacing;

            std::vector<std::string> tarr;

            FC_Font *font;

            TextArea(ShapeId sid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align);

            void InternalInit();
    };

}