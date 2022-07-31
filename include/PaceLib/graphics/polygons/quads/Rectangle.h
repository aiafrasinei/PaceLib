#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Rectangle : public Shape
    {
    public:

        /* Loads wconf file
        example format:
        {
            "dim" : ["W_2%", "H_10%", "W_7.5%", "H_3%"],
            "color" : [40, 40, 40, 255],
        }*/
        static void Create(ShapeId sid);
        static void Create(std::string name);
        
        static void Create(ShapeId sid, SDL_Rect dim, SDL_Color color);

        void SetRect(float x, float y, float w , float h);

        void SetRounded(bool rounded);

        void Draw();
        
        ~Rectangle();
    protected:         

    private:
        SDL_Rect rect;

        bool rounded;

        Rectangle(ShapeId sid, SDL_Rect dim, SDL_Color color);
    };

}
