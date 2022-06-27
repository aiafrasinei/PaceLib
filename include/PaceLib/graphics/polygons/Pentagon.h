#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Pentagon : public Shape
    {
    public:
        ~Pentagon();

        static void Create(std::string name, Shape *parent, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, SDL_Color color);

        //static void CreateRegular(float x1, float y1, float length);
     
        void SetDrawType(DrawTypes rtype);

        void Draw();

        void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
    protected:         

    private:
        SDL_Point points[6];

        SDL_Vertex verts[15];

        Pentagon(std::string name, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, SDL_Color color);
    };

}
