#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Triangle : public Shape
    {
    public:

//static methods

// json configuration

        /* Loads wconf file
        example format:
        {
            "x1" : 0,
            "y1" : 0,
            "x2" : 150,
            "y2" : 0,
            "x3" : 150,
            "y3" : 150,
            "color" : [40, 40, 40, 255]
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);

        //used when the triangle will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();

// programmatic

        static void Begin(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);

//end static methods

        void SetColor(SDL_Color color);

        void Draw();
        
        ~Triangle();
    protected:         

    private:
        SDL_Point points[4];

        SDL_Vertex verts[3];

        Triangle(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
    };

}
