#include "Tabber.h"
#include "Root.h"


using namespace PaceLib;

static bool once = true;
static int nrtabs = 0;
static int nrtitles = 0;

unsigned int Tabber::current = 1;
int Tabber::tabx = 0;

Tabber::Tabber(ShapeId sid, PropDimColor dco, PropFontText fto)
{
    if(sid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + dco.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + dco.rect.y;
    }
    
    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    this->name = sid.name;

    current = 1;

    bcounter = 0;
    
    top = {rect.x, rect.y, rect.w, rect.h/9};

    wtype = WidgetType::TAB;

    nrtabs = 0;

    tabx = 0;
}

Tabber::~Tabber()
{

}

void Tabber::Begin(ShapeId sid)
{
    if(std::filesystem::exists("wconfs/" + sid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + sid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropDimColor dco = {{dim[0], dim[1], dim[2], dim[3]}, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}};
        PropFontText fto = {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>()), ""};

        sid.parent->Add(new Tabber( sid, dco, fto));
    }
}

void Tabber::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    
    Tabber::Begin({(Widget *)root->GetCurrent(), name});
}

void Tabber::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    Tabber::Begin({(Widget *)root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);
}

void Tabber::EndBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tabber::Begin(ShapeId sid, PropDimColor dco, PropFontText fto)
{
    sid.parent->Add(new Tabber( sid, dco, fto));
}

void Tabber::SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    textColor.r = r;
    textColor.g = g;
    textColor.b = b;
    textColor.a = a;
}

void Tabber::Draw()
{
    if(!hidden) {
        if(once) {
            for(int i=0; i<shapesNames.size();i++) {
                char fc = shapesNames[i][0];
                if(fc == 't') {
                    shapes[i]->Hide();
                    shapes[current]->Show();
                }
            }
            once=false;
        }

        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
 
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 40, 40, 40, 255);
        SDL_RenderFillRect(Window::GetRenderer(), &top);

        SDL_SetRenderDrawColor(Window::GetRenderer(), 0, 0, 0, 255);

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void Tabber::BeginTabBlock(std::string text)
{
    Root *root = &Root::GetInstance();
    Tab *tab = (Tab *)root->GetCurrent();

    Button::Begin({root->GetCurrent(), "h_" + std::to_string(nrtitles)}, {{tabx, tab->GetRect().y/99, 40, tab->GetRect().y/17}, {120, 120, 120, 255}}, {Root::GetInstance().GetScene("Default")->GetFont("default"), text}, {V::MID, H::LEFT});

    Button *b = (Button *)root->GetCurrent()->Get("h_" + std::to_string(nrtitles));
    b->SetRectW(b->GetTextSize() + tab->GetRect().w/30);

    tabx = tabx + b->GetTextSize() + tab->GetRect().w/30 + tab->GetRect().w/99;

    b->onClickCallback = [btext = b->name]() {
        std::size_t pos = btext.find("_");
        int index = std::stoi(btext.substr(pos+1));
        current = 1 + index*2;

        once = true;
    };

    nrtitles++;

    Tab::Begin({tab, "t_" + std::to_string(nrtabs)} , { {0, tab->GetRect().y/13, tab->GetRect().w, tab->GetRect().h} , {tab->GetColor().r, tab->GetColor().g, tab->GetColor().b, tab->GetColor().a}});
    tab->Get("t_" + std::to_string(nrtabs))->Hide();
    root->SetCurrent(tab->Get("t_" + std::to_string(nrtabs)));
    root->GetCurrent()->SetParent(tab);
    nrtabs++;
}

void Tabber::EndTabBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
}

void Tabber::Update(SDL_Event *e)
{
    for(Shape *s : shapes) {
        s->Update(e);
    }
}
