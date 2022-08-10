#pragma once

#include "Text.h"


namespace PaceLib
{

    class Tooltip : public Widget
    {
        public:
            ~Tooltip();

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "text" : "text"
                "scene" : "Default",
                "font" : "default"
                "text_color" : [100, 100, 100, 255]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();

// programatic

            static void Begin(ShapeId sid, SDL_Color color, Align align={V::MID, H::MID});
            static void Begin(ShapeId sid, int w, int h, SDL_Color color, Align align={V::MID, H::MID});

//end static methods

            void Draw();

            void Add(Shape *s);

            void Update(SDL_Event *e);

        private:
            Tooltip(ShapeId sid, SDL_Rect shape, SDL_Color color);
    };



    class DefaultTooltip : public Widget
    {
        public:

//static methods

// json configuration

            /*
            {
                "text" : "this is a color label",
                "scene" : "Default",
                "font" : "default",
                "color" : "parent",
                "text_color" : [0, 0, 0, 255]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the tooltip will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();
            
// programmatic

            static void Begin(ShapeId sid, PropFontText fto, SDL_Color color, SDL_Color textColor);

//end static methods

            void Draw();

            void SetTextColor(SDL_Color color);
        private:
            Text *to;
            SDL_Color textColor;

            DefaultTooltip(ShapeId sid, PropFontText fto, SDL_Color color, SDL_Color textColor);
    };

}