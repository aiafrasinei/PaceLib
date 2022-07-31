#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Circle : public Shape
    {
    public:

//static methods

// json configuration

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x" : 100,
            "y" : 100,
            "radius" : 100
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name, bool hasChildren=false);
        static void End();

// programmatic

        static void Begin(ShapeId sid, float x, float y, float radius, SDL_Color color);

//end static methods

        void Draw();
        
        ~Circle();
    protected:         

    private:
        float x, y, radius;

        Circle(ShapeId sid, float x, float y, float radius, SDL_Color color);
    };

}
