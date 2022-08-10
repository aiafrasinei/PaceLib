#pragma once

#include "Widget.h"


namespace PaceLib
{

    class ThickLine : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 0,
            "y1" : 0,
            "x2" : 300,
            "y2" : 200,
            "size" : 2
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);

        //used when the thickline will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();
        
        static void Begin(ShapeId sid, int x1, int y1, int x2, int y2, int size, SDL_Color color);

        void Draw();

        ~ThickLine();

    protected:         

    private:
        SDL_Point points[4];
        SDL_Vertex verts[15];

        int x1, y1, x2, y2;

        ThickLine(ShapeId sid, int x1, int y1, int x2, int y2, int size, SDL_Color color);
    };

}
