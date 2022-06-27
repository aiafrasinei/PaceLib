#pragma once

#include "Widget.h"
#include "Label.h"
#include "Button.h"
#include "ButtonTex.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "../Text.h"


namespace PaceLib
{

    class Tab : public Widget
    {
        public:
            ~Tab();

            static void Create(WidgetId wid, PropDimColor in);

            Tab(WidgetId wid, PropDimColor in);

            void Draw();

            void Add(Shape *s);

            void Update(SDL_Event *e);

            Button *GetButton(std::string child);
            ButtonTex *GetButtonTex(std::string child);
            Label *GetLabel(std::string child);
            Widget *GetWidget(std::string child);
    };

}