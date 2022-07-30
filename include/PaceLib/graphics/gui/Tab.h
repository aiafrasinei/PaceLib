#pragma once

#include "Widget.h"
#include "Label.h"
#include "Button.h"
#include "ButtonTex.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"


namespace PaceLib
{

    class Tab : public Widget
    {
        public:
            ~Tab();

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_25%", "W_3%", "W_20%", "W_22%"],
                "color" : [80, 70, 80, 255]
            }*/
            static void Create(ShapeId wid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

            static void Create(ShapeId wid, PropDimColor in);

            Tab(ShapeId wid, PropDimColor in);

            void Draw();

            void Add(Shape *s);

            void Update(SDL_Event *e);

            Button *GetButton(std::string child);
            ButtonTex *GetButtonTex(std::string child);
            Label *GetLabel(std::string child);
            Widget *GetWidget(std::string child);
    };

}