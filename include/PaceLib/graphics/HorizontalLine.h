#pragma once

#include "Shape.h"
#include "Widget.h"


namespace PaceLib
{

    class HorizontalLine : public Shape
    {
    public:
        ~HorizontalLine();

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 400,
            "y1" : 200,
            "size" : 400
        }*/
        static void Create(WidgetId wid);
        static void Create(WidgetId wid, float x1, float y1, float size, SDL_Color color);


        void Draw();

    protected:         

    private:
        float x1, y1, x2, y2;

        HorizontalLine(WidgetId wid, float x1, float y1, float size, SDL_Color color);
    };

}
