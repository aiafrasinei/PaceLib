#pragma once

#include "Widget.h"
#include "DrawTypes.h"

namespace PaceLib
{

    class Ellipse : public Shape
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
            "rx" : 150,
            "ry" : 190
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);

        //used when the ellipse will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();

// programmatic

        static void Begin(ShapeId sid, float x, float y, float rx, float ry , SDL_Color color);

//end static methods

        void SetDrawType(DrawTypes rtype);

        void Draw();
        
        ~Ellipse();
    protected:         

    private:
        DrawTypes rtype;

        float x, y, rx, ry;

        Ellipse(ShapeId sid, float x, float y, float rx, float ry, SDL_Color color);
    };

}
