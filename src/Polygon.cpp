#include "Polygon.h"
#include "Window.h"

using namespace PaceLib;

Polygon::Polygon(const float * vx, const float * vy, int n)
{
    int i, nn;

    nn = n + 1;
    points = (SDL_Point*)malloc(sizeof(SDL_Point) * nn);

    for (i=0; i<n; i++)
    {
        points[i].x = vx[i];
        points[i].y = vy[i];
    }
    points[n].x = vx[0];
    points[n].y = vy[0];

    hidden = false;
    
    rtype = DrawTypes::OUTLINE;
}


Polygon::~Polygon()
{
    free(points);
}

Polygon *Polygon::Create(const float * vx, const float * vy, int n)
{
    return new Polygon(vx, vy, n);
}

void Polygon::Draw()
{
    if(!hidden) {
        if(rtype == DrawTypes::OUTLINE) {
            LoadDrawColor();

            SDL_RenderDrawLines(Window::GetRenderer(), points, n);
        } else if(rtype == DrawTypes::FILLED) {
        }
    }
}

void Polygon::SetDrawType(DrawTypes rtype)
{
    this->rtype = rtype;
}
