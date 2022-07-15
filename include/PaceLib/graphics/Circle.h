#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Circle : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x" : 100,
            "y" : 100,
            "radius" : 100
        }*/
        static void Create(WidgetId wid);
        static void Create(WidgetId wid, float x, float y, float radius, SDL_Color color);
     
        void Draw();
        
        ~Circle();
    protected:         

    private:
        float x, y, radius;

        Circle(WidgetId wid, float x, float y, float radius, SDL_Color color);
    };

}
