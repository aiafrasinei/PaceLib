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
            "x1" : 0,
            "y1" : 0,
            "x2" : 300,
            "y2" : 200,
            "color" : [0, 0, 0, 255]
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);

        //used when the line will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();

// programmatic

        static void Begin(ShapeId sid, LineProp prop);

//end static methods

        void Draw();

        ~Line();

    protected:         

    private:
        LineProp prop;
        int x1, y1, x2, y2;

        Line(ShapeId sid, LineProp prop);
    };

}
