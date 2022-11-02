#pragma once

#include "Widget.h"
#include "DrawTypes.h"

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
            "x" : 100,
            "y" : 100,
            "radius" : 100,
            "color" : [0, 0, 0, 255]
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);
        
        //used when the cicle will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();

// programmatic

        static void Begin(ShapeId sid, float x, float y, float radius, SDL_Color color);

//end static methods

        void SetDrawType(DrawTypes rtype);

        void Draw();
        
        ~Circle();
    protected:         

    private:
        DrawTypes rtype;

        float x, y, radius;

        Circle(ShapeId sid, float x, float y, float radius, SDL_Color color);
    };

}
