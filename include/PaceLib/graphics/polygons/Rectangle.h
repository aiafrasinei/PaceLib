#pragma once

#include "Shape.h"


namespace PaceLib
{

    class Rectangle : public Shape
    {
    public:
        ~Rectangle();

        static void Create(std::string name, Shape *parent, SDL_Rect shape, SDL_Color color);
        static void CreateSquare(std::string name, Shape *parent, int x, int y, int size, SDL_Color color);
        
        void SetRect(float x, float y, float w , float h);

        void SetRounded(bool rounded);

        void Draw();
        
    protected:         

    private:
        SDL_Rect rect;

        bool rounded;

        Rectangle(std::string name, Shape *parent, SDL_Rect shape, SDL_Color color);
    };

}
