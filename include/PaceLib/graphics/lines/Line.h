#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Line : public Shape
    {
    public:

//static methods

// json configuration

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 0,
            "y1" : 0,
            "x2" : 300,
            "y2" : 200
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);

        //used when the line will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();

// programmatic

        static void Begin(ShapeId sid, int x1, int y1, int x2, int y2, SDL_Color color);

//end static methods

        void Draw();

        ~Line();

    protected:         

    private:
        int x1, y1, x2, y2;

        Line(ShapeId sid, int x1, int y1, int x2, int y2, SDL_Color color);
    };

}
