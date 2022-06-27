#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Circle : public Shape
    {
    public:
        ~Circle();

        static void Create(std::string name, Shape *parent, float x, float y, float radius, SDL_Color color);
     
        void Draw();
        
    protected:         

    private:
        float x, y, radius;

        Circle(std::string name, float x, float y, float radius, SDL_Color color);
    };

}
