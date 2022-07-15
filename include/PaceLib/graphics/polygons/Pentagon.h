#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Pentagon : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "color" : [0, 0, 0, 255],
            "x1" : 100,
            "y1" : 200,
            "x2" : 150,
            "y2" : 200,
            "x3" : 200,
            "y3" : 350,
            "x4" : 70,
            "y4" : 320,
            "x5" : 50,
            "y5" : 230
        }*/
        static void Create(WidgetId wid);

        static void Create(WidgetId wid, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, SDL_Color color);

        static void CreateRegular(float x1, float y1, float length);
     
        void SetDrawType(DrawTypes rtype);

        void Draw();

        void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        ~Pentagon();
    protected:         

    private:
        SDL_Point points[6];

        SDL_Vertex verts[15];

        Pentagon(WidgetId wid, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, SDL_Color color);
    };

}
