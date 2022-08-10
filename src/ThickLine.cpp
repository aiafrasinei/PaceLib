#include "ThickLine.h"
#include "Window.h"
#include "Root.h"

using namespace PaceLib;

ThickLine::ThickLine(ShapeId sid, int x1, int y1, int x2, int y2, int size, SDL_Color color)
{
    //TODO

    SetColor(color.r, color.g, color.b, color.a);

    this->name = sid.name;
}

ThickLine::~ThickLine()
{

}

void ThickLine::Begin(ShapeId sid)
{
     if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int x1 = conf->Get("x1");
        int y1 = conf->Get("y1");
        int x2 = conf->Get("x2");
        int y2 = conf->Get("y2");
        int size = conf->Get("size");
        
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        sid.parent->Add(new ThickLine(sid, x1, y1, x2, y2, size, color));
    }
}


void ThickLine::Begin(std::string name)
{
    ThickLine::Begin({&Root::GetInstance(), name});
}

void ThickLine::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    ThickLine::Begin({root, name});

	Shape *prevParent = root->GetCurrent();
	root->SetCurrent(root->GetCurrent()->Get(name));
	root->GetCurrent()->SetParent(prevParent);
}

void ThickLine::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void ThickLine::Begin(ShapeId sid, int x1, int y1, int x2, int y2, int size, SDL_Color color)
{
    sid.parent->Add(new ThickLine(sid, x1, y1, x2, y2, size, color));
}

void ThickLine::Draw()
{
    if(!hidden) {
        for(int i=0; i<15; i++) {
            verts[i].color = {color.r, color.g, color.b, color.a};
        }

        SDL_RenderGeometry(Window::GetRenderer(), NULL, verts, 15, NULL, 0);
    }
}
