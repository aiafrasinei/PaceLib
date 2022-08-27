#include "Polygon.h"

using namespace PaceLib;

Polygon::Polygon(ShapeId sid, const float * vx, const float * vy, int n)
{
    int i, nn;

    nn = n + 1;
    points = (SDL_Point*)malloc(sizeof(SDL_Point) * nn);

    for (i=0; i<n; i++)
    {
        if(sid.parent->name == "root") {
            points[i].x = vx[i];
            points[i].y = vy[i];
        } else {
            points[i].x = static_cast<Widget *>(sid.parent)->GetRect().x + vx[i];
            points[i].y = static_cast<Widget *>(sid.parent)->GetRect().y + vy[i];
        }
    }

    if(sid.parent->name == "root") {
        points[n].x = vx[0];
        points[n].y = vy[0];
    } else {
        points[n].x = static_cast<Widget *>(sid.parent)->GetRect().x + vx[0];
        points[n].y = static_cast<Widget *>(sid.parent)->GetRect().y + vy[0];
    }

    hidden = false;
    
    rtype = DrawTypes::OUTLINE;

    name = sid.name;
}


Polygon::~Polygon()
{
    free(points);
}

void Polygon::Begin(ShapeId sid, const float * vx, const float * vy, int n)
{
    sid.parent->Add(new Polygon(sid, vx, vy, n));
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
