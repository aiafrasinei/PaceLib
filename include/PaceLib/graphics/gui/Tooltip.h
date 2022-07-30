#pragma once

#include "Text.h"


namespace PaceLib
{

    class Tooltip : public Widget
    {
        public:
            ~Tooltip();

            /* Loads wconf file
            example format:
            {
                "text" : "text"
                "scene" : "Default",
                "font" : "default"
                "text_color" : [100, 100, 100, 255]
            }*/
            static void Create(ShapeId wid);

            static void Begin(std::string name, bool hasChildren=false);
            static void End();

            static void Create(ShapeId wid, SDL_Color color, Align align={V::MID, H::MID});

            static void Create(ShapeId wid, int w, int h, SDL_Color color, Align align={V::MID, H::MID});

            void Draw();

            void Add(Shape *s);

            void Update(SDL_Event *e);

        private:
            Tooltip(ShapeId wid, SDL_Rect shape, SDL_Color color);
    };



    class DefaultTooltip : public Widget
    {
        public:
            /*
            {
                "text" : "this is a color label",
                "scene" : "Default",
                "font" : "default",
                "color" : "parent",
                "text_color" : [0, 0, 0, 255]
            }*/
            static void Create(ShapeId wid);
            static void Begin(std::string name, bool hasChildren=false);
            static void End();
            
            static void Create(ShapeId wid, PropFontText fto, SDL_Color color, SDL_Color textColor);
            static void Create(ShapeId wid, std::string text);

            void Draw();

            void SetTextColor(SDL_Color color);
        private:
            Text *to;
            SDL_Color textColor;

            DefaultTooltip(ShapeId wid, PropFontText fto, SDL_Color color, SDL_Color textColor);
    };

}