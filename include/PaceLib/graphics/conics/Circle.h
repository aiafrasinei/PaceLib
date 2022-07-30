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
        static void Create(ShapeId wid);
        static void Create(std::string name);
        
        static void Create(ShapeId wid, float x, float y, float radius, SDL_Color color);
     
        void Draw();
        
        ~Circle();
    protected:         

    private:
        float x, y, radius;

        Circle(ShapeId wid, float x, float y, float radius, SDL_Color color);
    };

}
