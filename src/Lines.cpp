#include "Lines.h"
#include "Root.h"

using namespace PaceLib;

Lines::Lines(ShapeId sid, std::vector<SDL_Point> verts)
{
    this->verts = verts;

    for (int i=0; i<verts.size(); i++)
    {
        if(sid.parent->name != "root") {
            verts[i].x = static_cast<Widget *>(sid.parent)->GetRect().x + verts[i].x;
            verts[i].y = static_cast<Widget *>(sid.parent)->GetRect().y + verts[i].y;
        }
    }

    hidden = false;

    name = sid.name;
}


Lines::~Lines()
{
}

void Lines::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Lines.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        std::vector<int> all_verts = conf->Get("verts").get<std::vector<int>>();

        std::vector<SDL_Point> verts;

        int vsize = all_verts.size()/2;
        int index = 0;
        for(int i=0; i<vsize; i++) {
            SDL_Point v;
            v.x = all_verts[index];
            v.y = all_verts[++index];
            verts.push_back(v);
            index++;
        }

        sid.parent->Add(new Lines(sid, verts));
    }
}

void Lines::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    Lines::Begin({root->GetCurrent(), name});
}

void Lines::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Lines::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Lines::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}


void Lines::Begin(ShapeId sid, std::vector<SDL_Point> verts)
{
    sid.parent->Add(new Lines(sid, verts));
}

void Lines::Draw()
{
    if(!hidden) {
        LoadDrawColor();
        SDL_RenderDrawLines(Window::GetRenderer(), &verts[0], verts.size());
    }
}
