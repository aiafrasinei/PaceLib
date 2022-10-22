#include "graphics/conics/Ellipse.h"
#include "Root.h"


using namespace PaceLib;

Ellipse::Ellipse(ShapeId sid, float x, float y, float rx, float ry, SDL_Color color)
{
    if(sid.parent->name == "root") {
        this->x = x;
        this->y = y;
        this->rx = rx;
        this->ry = ry;
    } else {
        this->x = static_cast<Widget *>(sid.parent)->GetRect().x + x;
        this->y = static_cast<Widget *>(sid.parent)->GetRect().y + y;
        this->rx = static_cast<Widget *>(sid.parent)->GetRect().x + rx;
        this->ry = static_cast<Widget *>(sid.parent)->GetRect().y + ry;
    }

    hidden = false;

    rtype = DrawTypes::FILLED;
    
    SetColor(color);
    this->name = sid.name;
}

Ellipse::~Ellipse()
{

}

void Ellipse::SetDrawType(DrawTypes rtype)
{
    this->rtype = rtype;
}

void Ellipse::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Ellipse.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        int x = conf->Get("x");
        int y = conf->Get("y");
        int rx = conf->Get("rx");
        int ry = conf->Get("ry");
        SDL_Color color = { conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]};

        sid.parent->Add(new Ellipse(sid, x, y, rx, ry, color));
    }
}

void Ellipse::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Ellipse::Begin({root->GetCurrent(), name});
}

void Ellipse::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Ellipse::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Ellipse::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Ellipse::Begin(ShapeId sid, float x, float y, float rx, float ry, SDL_Color color)
{
    sid.parent->Add(new Ellipse(sid, x, y, rx, ry, color));
}

void Ellipse::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        //TODO
        if(rtype == DrawTypes::OUTLINE) {
        } else if (rtype == DrawTypes::FILLED) {

        }
    }
}
