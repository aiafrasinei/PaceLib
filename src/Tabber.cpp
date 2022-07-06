#include "Tabber.h"
#include "Window.h"
#include "Root.h"


using namespace PaceLib;

static bool once = true;
static int nrtabs = 0;
static int nrtitles = 0;

unsigned int Tabber::current = 0;

Tabber::Tabber(WidgetId wid, PropDimColor dco, PropFontText fto)
{
    if(wid.parent->name == "root") {
        rect.x = dco.rect.x;
        rect.y = dco.rect.y;
    } else {
        rect.x = wid.parent->GetRect().x + dco.rect.x;
        rect.y = wid.parent->GetRect().y + dco.rect.y;
    }
    rect.w = dco.rect.w;
    rect.h = dco.rect.h;

    hidden = false;
    
    color = {dco.color.r, dco.color.g, dco.color.b, dco.color.a};

    textColor = {0, 0, 0, 255};

    this->name = wid.name;

    current = 0;
    xb = rect.y/99;

    bcounter = 0;
    
    top = {rect.x, rect.y, rect.w, rect.h/9};

    wtype = WidgetType::TAB;
}

Tabber::~Tabber()
{

}

void Tabber::Create(WidgetId wid)
{
    if(std::filesystem::exists("wconfs/" + wid.name + ".conf")) {
        Configuration *conf = new Configuration("wconfs/" + wid.name + ".conf");

        int dim[4];
        Widget::ParseDim(dim, conf);

        PropDimColor dco = {{dim[0], dim[1], dim[2], dim[3]}, {conf->Get("color")[0], conf->Get("color")[1], conf->Get("color")[2], conf->Get("color")[3]}};
        PropFontText fto = {Root::GetInstance().GetScene(conf->Get("scene").get<std::string>()).GetFont(conf->Get("font").get<std::string>()), ""};

        wid.parent->Add(new Tabber( wid, dco, fto));
    }
}

void Tabber::Create(WidgetId wid, PropDimColor dco, PropFontText fto)
{
    wid.parent->Add(new Tabber( wid, dco, fto));
}

void Tabber::Create(WidgetId wid, PropDimColor dco)
{
    wid.parent->Add(new Tabber( wid, {dco.rect, dco.color}, {Root::GetInstance().GetScene("Default").GetFont("default"), ""}));
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
            for(Tab *tab : tabs) {
                tab->Hide();
            }
            tabs[current]->Show();
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

        for(Shape *w : buttons) {
            w->Draw();
        }

        for(Shape *w : tabs) {
            w->Draw();
        }
    }
}

void Tabber::AddTab(std::string text)
{
    titles.push_back(text);

    buttons.push_back(new Button({this, "h_" + std::to_string(nrtitles)}, {{xb, rect.y/99, 40, rect.y/17}, {120, 120, 120, 255}}, {Root::GetInstance().GetScene("Default").GetFont("default"), text}, {V::MID, H::LEFT}));
    Button *b = ((Button *)buttons[nrtitles]);
    b->SetRectW(b->GetTextSize() + rect.w/30);
    xb = xb + b->GetTextSize() + rect.w/30 + rect.w/99;

    buttons[nrtitles]->onClickCallback = [btext = buttons[nrtitles]->GetText()]() {
        std::size_t pos = btext.find("_");
        current = std::stoi(btext.substr(pos+1));
        once = true;
    };

    nrtitles++;

    tabs.push_back(new Tab({this, "t_" + std::to_string(nrtabs)} , { {0, rect.y/13, rect.w, rect.h} , {color.r, color.g, color.b, color.a} }));
    tabs[nrtabs]->Hide();
    nrtabs++;
}

void Tabber::Update(SDL_Event *e)
{
    for(Shape *s : shapes) {
        s->Update(e);
    }

    for(Shape *w : buttons) {
        w->Update(e);
    }

    for(Shape *w : tabs) {
        w->Update(e);
    }
}


Tab *Tabber::GetTab(int index)
{
    return tabs[index];
}
