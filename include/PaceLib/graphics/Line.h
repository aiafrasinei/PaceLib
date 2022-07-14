#pragma once

#include "Shape.h"
#include "Widget.h"


namespace PaceLib
{

    class Line : public Shape
    {
    public:
        ~Line();

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 0,
            "y1" : 0,
            "x2" : 300,
            "y2" : 200
        }*/
        static void Create(WidgetId wid);
        static void Create(WidgetId wid, int x1, int y1, int x2, int y2, SDL_Color color);

        void Draw();

    protected:         

    private:
        int x1, y1, x2, y2;

        Line(WidgetId wid, int x1, int y1, int x2, int y2, SDL_Color color);
    };

}
