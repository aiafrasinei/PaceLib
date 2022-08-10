#pragma once

#include "Widget.h"


namespace PaceLib
{

    class Rectangle : public Shape
    {
    public:

//static methods

// json configuration

        /* Loads wconf file
        example format:
        {
            "dim" : ["W_2%", "H_10%", "W_7.5%", "H_3%"],
            "color" : [40, 40, 40, 255],
        }*/
        static void Begin(ShapeId sid);
        static void Begin(std::string name);

        //used when the rectangle will have child elements
        static void BeginBlock(std::string name);
        static void EndBlock();
        
// programmatic

        static void Begin(ShapeId sid, SDL_Rect dim, SDL_Color color);

//end static methods

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
