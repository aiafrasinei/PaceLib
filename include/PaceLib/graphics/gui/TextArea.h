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

            //TODO
            static void Create(ShapeId wid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

            static void Create(ShapeId wid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align={V::MID, H::MID});

            static void Create(ShapeId wid, PropDimColor dco, std::vector<std::string> tarr, Align align={V::MID, H::MID});

            void SetTextAlign(Align align);

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void SetTextSpacing(int size);

            void Draw();

        private:
            std::vector<Text *> tos;

            SDL_Color textColor;

            Align align;

            int textSpacing;

            TextArea(ShapeId wid, PropDimColor dco, FC_Font *font, std::vector<std::string> tarr, Align align);

            void InternalAlign(Align align);
    };

}