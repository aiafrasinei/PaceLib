#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Hexagon : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 0,
            "y1" : 0,
            "x2" : 0,
            "y2" : 0,
            "x3" : 0,
            "y3" : 0,
            "x4" : 0,
            "y4" : 0,
            "x5" : 0,
            "y5" : 0,
            "x6" : 0,
            "y6" : 0
        }*/
        static void Create(WidgetId wid);
        static void Create(std::string name);

        static void Create(WidgetId wid, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6, SDL_Color color);
     
        static void CreateRegular(float x1, float y1, float length);

        void SetDrawType(DrawTypes rtype);

        void Draw();

        void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        ~Hexagon();
    protected:         

    private:
        SDL_Point points[7];

        SDL_Vertex verts[18];

        Hexagon(WidgetId wid, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, float x6, float y6, SDL_Color color);
    };

}
