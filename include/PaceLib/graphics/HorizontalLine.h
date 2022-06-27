#pragma once

#include "Shape.h"


namespace PaceLib
{

    class HorizontalLine : public Shape
    {
    public:
        ~HorizontalLine();

        static void Create(std::string name, Shape *parent, float x1, float y1, float size, SDL_Color color);


        void Draw();

    protected:         

    private:
        float x1, y1, x2, y2;

        HorizontalLine(std::string name, float x1, float y1, float size, SDL_Color color);
    };

}
