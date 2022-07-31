#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Triangle : public Shape
    {
    public:

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
        static void Create(ShapeId sid);
        static void Create(std::string name);

        static void Create(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
     
        void SetDrawType(DrawTypes rtype);

        void Draw();

        void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        ~Triangle();
    protected:         

    private:
        SDL_Point points[4];

        SDL_Vertex verts[3];

        Triangle(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
    };

}
