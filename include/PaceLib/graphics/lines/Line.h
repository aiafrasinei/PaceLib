#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Line : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 0,
            "y1" : 0,
            "x2" : 300,
            "y2" : 200
        }*/
        static void Create(ShapeId wid);
        static void Create(std::string name);
        
        static void Create(ShapeId wid, int x1, int y1, int x2, int y2, SDL_Color color);

        void Draw();

        ~Line();

    protected:         

    private:
        int x1, y1, x2, y2;

        Line(ShapeId wid, int x1, int y1, int x2, int y2, SDL_Color color);
    };

}
