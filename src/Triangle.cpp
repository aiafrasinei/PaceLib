#include "Triangle.h"
#include "Window.h"

using namespace PaceLib;


Triangle::Triangle(WidgetId wid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
    SetColor(color.r, color.g, color.b, color.a);

    if(wid.parent->name == "root") {
        points[0] = {static_cast<int>(x1), static_cast<int>(y1)};
        points[1] = {static_cast<int>(x2), static_cast<int>(y2)};
        points[2] = {static_cast<int>(x3), static_cast<int>(y3)};
        points[3] = {static_cast<int>(x1), static_cast<int>(y1)};
    } else {
        points[0] = {static_cast<int>(wid.parent->GetRect().x + x1), static_cast<int>(wid.parent->GetRect().y + y1)};
        points[1] = {static_cast<int>(wid.parent->GetRect().x + x2), static_cast<int>(wid.parent->GetRect().y + y2)};
        points[2] = {static_cast<int>(wid.parent->GetRect().x + x3), static_cast<int>(wid.parent->GetRect().y + y3)};
        points[3] = {static_cast<int>(wid.parent->GetRect().x + x1), static_cast<int>(wid.parent->GetRect().y + y1)};
    }
    

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

    this->name = wid.name;
}

Triangle::~Triangle()
{

}

void Triangle::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int x2 = conf->Get("x2");
        int y2 = conf->Get("y2");
        int x3 = conf->Get("x3");
        int y3 = conf->Get("y3");
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};
        
        wid.parent->Add(new Triangle(wid, x1, y1, x2, y2, x3, y3, color));
    }
}

void Triangle::Create(WidgetId wid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
    wid.parent->Add(new Triangle(wid, x1, y1, x2, y2, x3, y3, color));
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
