#include "Pentagon.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

Pentagon::Pentagon(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, SDL_Color color)
{
    if(sid.parent->name == "root") {
        points[0] = {static_cast<int>(x1), static_cast<int>(y1)};
        points[1] = {static_cast<int>(x2), static_cast<int>(y2)};
        points[2] = {static_cast<int>(x3), static_cast<int>(y3)};
        points[3] = {static_cast<int>(x4), static_cast<int>(y4)};
        points[4] = {static_cast<int>(x5), static_cast<int>(y5)};
        points[5] = {static_cast<int>(x1), static_cast<int>(y1)};
    } else {
        points[0] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x1), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y1)};
        points[1] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x2), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y2)};
        points[2] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x3), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y3)};
        points[3] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x4), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y4)};
        points[4] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x5), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y5)};
        points[5] = {static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().x + x1), static_cast<int>(static_cast<Widget *>(sid.parent)->GetRect().y + y1)};
    }

    float left = 0;
    float right = 0;
    float top = 0;
    float bottom = 0;

    float xarr[] = {x1, x2, x3, x4, x5};
    float yarr[] = {y1, y2, y3, y4, y5};

    for(float f : xarr) {
        if (f < left) {
            left = f;
        } 
    }

    for(float f : xarr) {
        if (f > right) {
            right = f;
        } 
    }

    for(float f : yarr) {
        if (f < top) {
            top = f;
        } 
    }

    for(float f : yarr) {
        if (f > bottom) {
            bottom = f;
        } 
    }

    float middlex = (left + right)/2;
    float middley = (top + bottom)/2;

    verts[0].position.x = x1;
	verts[0].position.y = y1;
	
	verts[1].position.x = x2;
	verts[1].position.y = y2;

	verts[2].position.x = middlex;
	verts[2].position.y = middley;

    verts[3].position.x = x2;
	verts[3].position.y = y2;

    verts[4].position.x = x3;
	verts[4].position.y = y3;

    verts[5].position.x = middlex;
	verts[5].position.y = middley;

    verts[6].position.x = x3;
	verts[6].position.y = y3;

    verts[7].position.x = x4;
	verts[7].position.y = y4;

    verts[8].position.x = middlex;
	verts[8].position.y = middley;

    verts[9].position.x = x4;
	verts[9].position.y = y4;

    verts[10].position.x = x5;
	verts[10].position.y = y5;

    verts[11].position.x = middlex;
	verts[11].position.y = middley;

    verts[12].position.x = x5;
	verts[12].position.y = y5;

    verts[13].position.x = x1;
	verts[13].position.y = y1;

    verts[14].position.x = middlex;
	verts[14].position.y = middley;

    for(int i=0; i<15; i++) {
        verts[i].color = {color.r, color.g, color.b, color.a};
    }

    hidden = false;
    
    rtype = DrawTypes::OUTLINE;

    SetColor(color.r, color.g, color.b, color.a);

    this->name = sid.name;
}

Pentagon::~Pentagon()
{

}

void Pentagon::Begin(ShapeId sid)
{
     if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int x2 = conf->Get("x2");
        int y2 = conf->Get("y2");
        int x3 = conf->Get("x3");
        int y3 = conf->Get("y3");
        int x4 = conf->Get("x4");
        int y4 = conf->Get("y4");
        int x5 = conf->Get("x5");
        int y5 = conf->Get("y5");
        
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        sid.parent->Add(new Pentagon(sid, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, color));
    }
}

void Pentagon::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Pentagon::Begin({root->GetCurrent(), name});
}

void Pentagon::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Pentagon::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Pentagon::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Pentagon::Begin(ShapeId sid, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5, SDL_Color color)
{
    sid.parent->Add(new Pentagon(sid, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, color));
}

/*Pentagon *Pentagon::CreateRegular(float x1, float y1, float length)
{
    return NULL;
}*/

void Pentagon::Draw()
{
    if(!hidden) {
        if(rtype == DrawTypes::OUTLINE) {
            LoadDrawColor();
            SDL_RenderDrawLines(Window::GetRenderer(), points, 6);
        } else if(rtype == DrawTypes::FILLED) {
            SDL_RenderGeometry(Window::GetRenderer(), NULL, verts, 15, NULL, 0);
        }
    }
}

void Pentagon::DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        if(!hidden) {
            if(rtype == DrawTypes::OUTLINE) {
                SDL_RenderDrawLines(Window::GetRenderer(), points, 6);
            } else if(rtype == DrawTypes::FILLED) {
                for(int i=0; i<15; i++) {
                    verts[i].color = {r, g, b, a};
                }

                SDL_RenderGeometry(Window::GetRenderer(), NULL, verts, 15, NULL, 0);
            }
        }
}

void Pentagon::SetDrawType(DrawTypes rtype)
{
    this->rtype = rtype;
}
