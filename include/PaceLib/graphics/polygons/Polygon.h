#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Polygon : public Shape
    {
    public:
        Polygon(const float *vx, const float *vy, int n);
        ~Polygon();

        static Polygon *Create(const float *vx, const float *vy, int n);
     
        void SetDrawType(DrawTypes rtype);

        void Draw();
        
    protected:         

    private:
        SDL_Point* points;
        
        const float * vx;
        const float * vy;
        int n;

        DrawTypes rtype;
    };

}
