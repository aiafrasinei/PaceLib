#include "Triangle.h"
#include "Root.h"

using namespace PaceLib;


Triangle::Triangle(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
    SetColor(color);

    if(sid.parent->name == "root") {
        points[0] = {static_cast<int>(x1), static_cast<int>(y1)};
        points[1] = {static_cast<int>(x2), static_cast<int>(y2)};
        points[2] = {static_cast<int>(x3), static_cast<int>(y3)};
        points[3] = {static_cast<int>(x1), static_cast<int>(y1)};
    } else {
        points[0] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x1), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y1)};
        points[1] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x2), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y2)};
        points[2] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x3), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y3)};
        points[3] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x1), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y1)};
    }
    

    verts[0].position.x = points[0].x;
	verts[0].position.y = points[0].y;
    verts[0].color = {color.r, color.g, color.b, color.a};
	
	verts[1].position.x = points[1].x;
	verts[1].position.y = points[1].y;
    verts[1].color = {color.r, color.g, color.b, color.a};

	verts[2].position.x = points[2].x;
	verts[2].position.y = points[2].y;
    verts[2].color = {color.r, color.g, color.b, color.a};

    hidden = false;

    this->name = sid.name;
}

Triangle::~Triangle()
{

}

void Triangle::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Triangle.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int x2 = conf->Get("x2");
        int y2 = conf->Get("y2");
        int x3 = conf->Get("x3");
        int y3 = conf->Get("y3");
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};
        
        sid.parent->Add(new Triangle(sid, x1, y1, x2, y2, x3, y3, color));
    }
}

void Triangle::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Triangle::Begin({root->GetCurrent(), name});
}

void Triangle::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Triangle::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);

    Widget *c = ((Widget *)root->GetCurrent());
    root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void Triangle::EndBlock()
{
    Root *root = &Root::GetInstance();

    Widget *c = ((Widget *)root->GetCurrent());
    root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Triangle::Begin(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color)
{
    sid.parent->Add(new Triangle(sid, x1, y1, x2, y2, x3, y3, color));
}

void Triangle::SetColor(SDL_Color color)
{
    this->color = color;
    verts[0].color = {color.r, color.g, color.b, color.a};
    verts[1].color = {color.r, color.g, color.b, color.a};
    verts[2].color = {color.r, color.g, color.b, color.a};
}

void Triangle::Draw() {
        if(!hidden) {
            SDL_RenderGeometry(Window::GetRenderer(), nullptr, verts, 3, nullptr, 0);
        }
}
