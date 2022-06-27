#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Triangle : public Shape
    {
    public:
        ~Triangle();

        static void Create(std::string name, Shape *parent, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
     
        void SetDrawType(DrawTypes rtype);

        void Draw();

        void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
    protected:         

    private:
        SDL_Point points[4];

        SDL_Vertex verts[3];

        Triangle(std::string name, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
    };

}
