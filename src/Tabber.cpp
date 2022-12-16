#include "Tabber.h"
#include "Root.h"


using namespace PaceLib;

static bool once = true;
static int nrtabs = 0;
static int nrtitles = 0;

unsigned int Tabber::current = 1;
int Tabber::tabx = 0;

Tabber::Tabber(ShapeId sid, TabberProp prop)
{
    this->prop = prop;

    rect = prop.rect;

    if(sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.rect.y;
    }

    this->prop.rect = rect;

    hidden = false;

    this->name = sid.name;

    current = 1;

    bcounter = 0;
    
    top = {rect.x, rect.y, rect.w, Window::height*prop.headerHeight/100};

    wtype = WidgetType::TABBER;

    nrtabs = 0;

    tabx = Window::height*1/100;
}

Tabber::~Tabber()
{

}

void Tabber::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_Tabber.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        TabberProp prop = LoadTabberProp(conf);

        sid.parent->Add(new Tabber( sid, prop));
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
    root->UpdateAbsoluteCoords({0, 0});
}

void Tabber::Begin(ShapeId sid, TabberProp prop)
{
    sid.parent->Add(new Tabber(sid, prop));
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

        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.backgroundColor.r, prop.backgroundColor.g, prop.backgroundColor.b, prop.backgroundColor.a);
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.headerBackgroundColor.r, prop.headerBackgroundColor.g, prop.headerBackgroundColor.b, prop
.headerBackgroundColor.a);
        SDL_RenderFillRect(Window::GetRenderer(), &top);

        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r, prop.borderColor.g, prop.borderColor.b, prop.borderColor.a);
        SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void Tabber::BeginTabBlock(std::string text)
{
    Root *root = &Root::GetInstance();
    Tabber *tabber = (Tabber *)root->GetCurrent();

    LabelProp prop = {
                        {tabx, Window::height*1/100, 0, Window::height*(tabber->prop.headerHeight-1)/100},
                        root->GetScene("Default")->GetFont("default"),
                        text,
                        tabber->GetProp().buttonsTextColor,
                        tabber->GetProp().buttonsTextAlign,
                        tabber->GetProp().buttonsBackgroundColor,
                        tabber->GetProp().buttonsBorderColor,
                        tabber->GetProp().buttonsHighlightColor
                    };

    Button::Begin({root->GetCurrent(), "h_" + std::to_string(nrtitles)}, prop);

    Button *b = (Button *)root->GetCurrent()->Get("h_" + std::to_string(nrtitles));

    float real_width = b->GetTextSize() + b->GetTextSize()/3;
    b->SetRectW(real_width);
    prop.rect.w = real_width;
    b->SetTextAlign(prop.align);

    tabx = tabx + real_width + tabber->GetRect().w/99;

    b->onClickCallback = [btext = b->name]() {
        std::size_t pos = btext.find("_");
        int index = std::stoi(btext.substr(pos+1));
        current = 1 + index*2;

        once = true;
    };

    nrtitles++;

    Tab::Begin({tabber, "t_" + std::to_string(nrtabs)} , { {0, Window::height*tabber->prop.headerHeight/100, tabber->GetRect().w, tabber->GetRect().h} , tabber->GetProp().backgroundColor});
    tabber->GetTab("t_" + std::to_string(nrtabs))->Hide();
    root->SetCurrent(tabber->GetTab("t_" + std::to_string(nrtabs)));
    root->GetCurrent()->SetParent(tabber);
    nrtabs++;
}

void Tabber::EndTabBlock()
{
    Root *root = &Root::GetInstance();
    root->SetCurrent(root->GetCurrent()->GetParent());
    root->UpdateAbsoluteCoords({0, 0});
}

void Tabber::Update(SDL_Event *e)
{
    for(Shape *s : shapes) {
        if(!s->IsHidden())
            s->Update(e);
    }
}

TabberProp Tabber::GetProp()
{
    return prop;
}

TabberProp Tabber::LoadTabberProp(Configuration *conf)
{
    int dim[4];
    Root::ParseDim(dim, conf);

    HorizontalAlign align;
    if (conf->Get("buttons_text_align") == "left")
        align.halign = H::LEFT;
    else if (conf->Get("buttons_text_align") == "mid")
        align.halign = H::MID;
    else if (conf->Get("buttons_text_align") == "right")
        align.halign = H::RIGHT;

    Root *root = &Root::GetInstance();

    SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
    SDL_Color backgroundColor = Widget::ParseVar("background", conf, root->GetVars());
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
    SDL_Color headerBackgroundColor= Widget::ParseVar("header_background", conf, root->GetVars());
    int headerHeightPercent = conf->Get("header_height").get<int>();
    FC_Font *buttonsFont = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("buttons_font").get<std::string>());
    SDL_Color buttonsTextColor = Widget::ParseVar("buttons_text_color", conf, root->GetVars());
    SDL_Color buttonsBackgroundColor = Widget::ParseVar("buttons_background", conf, root->GetVars());
    SDL_Color buttonsBorderColor = Widget::ParseVar("buttons_border", conf, root->GetVars());
    SDL_Color buttonsHighlightColor = Widget::ParseVar("buttons_highlight", conf, root->GetVars());

    TabberProp prop = {
                        dimr,
                        backgroundColor,
                        borderColor,
                        headerBackgroundColor,
                        headerHeightPercent,
                        buttonsFont,
                        buttonsTextColor,
                        align,
                        buttonsBackgroundColor,
                        buttonsBorderColor,
                        buttonsHighlightColor
                    };
    return prop;
}

Tab *Tabber::GetTab(std::string child)
{
    return static_cast<Tab *>(this->Get(child));
}

Tab *Tabber::GetTab(int index)
{
    return static_cast<Tab *>(this->Get("t_" + std::to_string(index)));
}