#include "Triangle.h"
#include "Window.h"

using namespace PaceLib;


Triangle::Triangle(std::string name, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
    SetColor(color.r, color.g, color.b, color.a);

    points[0] = {static_cast<int>(x1), static_cast<int>(y1)};
    points[1] = {static_cast<int>(x2), static_cast<int>(y2)};
    points[2] = {static_cast<int>(x3), static_cast<int>(y3)};
    points[3] = {static_cast<int>(x1), static_cast<int>(y1)};

    verts[0].position.x = x1;
	verts[0].position.y = y1;
    verts[0].color = {color.r, color.g, color.b, color.a};
	
	verts[1].position.x = x2;
	verts[1].position.y = y2;
    verts[1].color = {color.r, color.g, color.b, color.a};

	verts[2].position.x = x3;
	verts[2].position.y = y3;
    verts[2].color = {color.r, color.g, color.b, color.a};

    hidden = false;
    
    rtype = DrawTypes::OUTLINE;

    this->name = name;
}

Triangle::~Triangle()
{

}

void Triangle::Create(std::string name, Shape *parent, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
    parent->Add(new Triangle(name, x1, y1, x2, y2, x3, y3, color));
}


void Triangle::Draw() {
        if(!hidden) {
            if(rtype == DrawTypes::OUTLINE) {
                SDL_RenderDrawLines(Window::GetRenderer(), points, 4);
            } else if(rtype == DrawTypes::FILLED) {
                SDL_RenderGeometry(Window::GetRenderer(), NULL, verts, 3, NULL, 0);
            }
        }
}
