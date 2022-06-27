#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Line : public Shape
    {
    public:
        ~Line();

        static void Create(std::string name, Shape *parent, float x1, float y1, float x2, float y2, SDL_Color color);

        void Draw();

    protected:         

    private:
        float x1, y1, x2, y2;

        Line(std::string name, float x1, float y1, float x2, float y2, SDL_Color color);
    };

}
