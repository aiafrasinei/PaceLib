#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Ellipse : public Shape
    {
    public:
        ~Ellipse();

        static void Create(std::string name, Shape *parent, float x, float y, float rx, float ry , SDL_Color color);
        
        void SetDrawType(DrawTypes rtype);

        void Draw();
        
    protected:         

    private:
        float x, y, rx, ry;

        Ellipse(std::string name, float x, float y, float rx, float ry, SDL_Color color);
    };

}
