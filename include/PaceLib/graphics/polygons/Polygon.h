#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Polygon : public Shape
    {
    public:

        static void Create(ShapeId sid, const float *vx, const float *vy, int n);
     
        void SetDrawType(DrawTypes rtype);

        void Draw();

        ~Polygon();
        
    protected:         

    private:
        SDL_Point* points;
        
        const float * vx;
        const float * vy;
        int n;

        DrawTypes rtype;

        Polygon(ShapeId sid, const float *vx, const float *vy, int n);
    };

}
