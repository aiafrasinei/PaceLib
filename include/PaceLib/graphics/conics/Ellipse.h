#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Ellipse : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x" : 100,
            "y" : 100,
            "rx" : 150,
            "ry" : 190
        }*/
        static void Create(ShapeId wid);
        static void Create(std::string name);

        static void Create(ShapeId wid, float x, float y, float rx, float ry , SDL_Color color);
        
        void SetDrawType(DrawTypes rtype);

        void Draw();
        
        ~Ellipse();
    protected:         

    private:
        float x, y, rx, ry;

        Ellipse(ShapeId wid, float x, float y, float rx, float ry, SDL_Color color);
    };

}
