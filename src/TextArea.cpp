#include "TextArea.h"
#include "Root.h"

using namespace PaceLib;

TextArea::TextArea(ShapeId sid, MultiItemsProp prop)
{
    this->prop = prop;
    rect = prop.rect;

    if(sid.parent->name != "root") {
        rect.x = static_cast<Widget *>(sid.parent)->GetRect().x + prop.rect.x;
        rect.y = static_cast<Widget *>(sid.parent)->GetRect().y + prop.rect.y;
    }

    this->prop.rect = rect;
    color = prop.backgroundColor;
    borderColor = prop.borderColor;

    hidden = false;

    textSpacing = 20;

    this->name = sid.name;

    wtype = WidgetType::TEXTAREA;
}

TextArea::~TextArea()
{

}

void TextArea::Begin(ShapeId sid)
{
    std::string path = "wconfs/" + sid.name + "_TextArea.conf";
    if(std::filesystem::exists(path)) {
        Configuration *conf = new Configuration(path);

        MultiItemsProp prop = LoadTextAreaProp(conf);

        TextArea *ta = new TextArea(sid, prop);
        sid.parent->Add(ta);

        ta->InternalInit();
    }
}

void TextArea::Begin(std::string name)
{
    Root *root = &Root::GetInstance();
    TextArea::Begin({root->GetCurrent(), name});
}

void TextArea::BeginBlock(std::string name)
{
    Root *root = &Root::GetInstance();
    TextArea::Begin({root->GetCurrent(), name});

    Shape *prevParent = root->GetCurrent();
    root->SetCurrent(root->GetCurrent()->Get(name));
    root->GetCurrent()->SetParent(prevParent);

    Widget *c = ((Widget *)root->GetCurrent());
    root->PushAbsoluteCoords({c->GetRect().x, c->GetRect().y});
}

void TextArea::EndBlock()
{
    Root *root = &Root::GetInstance();

    Widget *c = ((Widget *)root->GetCurrent());
    root->PopAbsoluteCoords({c->GetRect().x, c->GetRect().y});

    root->SetCurrent(root->GetCurrent()->GetParent());
}

void TextArea::Begin(ShapeId sid, MultiItemsProp prop)
{
    TextArea *ta = new TextArea(sid, prop);
    sid.parent->Add(ta);

    Root *root = &Root::GetInstance();
    ((TextArea *)root->GetCurrent()->Get(sid.name))->InternalInit();
}

void TextArea::Draw()
{
    if(!hidden) {
        SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(Window::GetRenderer(), &rect);

        SDL_SetRenderDrawColor(Window::GetRenderer(), prop.borderColor.r, prop.borderColor.g, prop.borderColor.b, prop.borderColor.a);
        SDL_RenderDrawRect(Window::GetRenderer(), &rect);

        for(Shape *w : shapes) {
            w->Draw();
        }
    }
}

void TextArea::SetTextSpacing(int size)
{
    this->textSpacing = size;
}

void TextArea::InternalInit()
{
    Root *root = &Root::GetInstance();
    TextArea *ta = (TextArea *)root->GetCurrent()->Get(name);

    int ry = rect.y;
    int i=0;
    for (std::string text : prop.tarr) {

        TextProp tprop = {
            rect.x + rect.w/50,
            ry,
            prop.font,
            text,
            prop.textColor
        };

        Text::Begin({ta, ta->name+"_text" + std::to_string(i)}, tprop);

        Text *to = (Text *)ta->Get(name + "_text" + std::to_string(i));
        to->SetX(GetRect().x + rect.w/20);
        to->SetY(ry);

        ry = ry + 20;
        i++;
    }
    
}

MultiItemsProp TextArea::LoadTextAreaProp(Configuration *conf)
{
    int dim[4];
    Root::ParseDim(dim, conf);

    Root *root = &Root::GetInstance();

    SDL_Rect dimr = {dim[0], dim[1], dim[2], dim[3]};
    SDL_Color backgroundColor = Widget::ParseVar("background", conf, root->GetVars());
    SDL_Color borderColor = Widget::ParseVar("border", conf, root->GetVars());
    FC_Font *font = root->GetScene(conf->Get("scene").get<std::string>())->GetFont(conf->Get("font").get<std::string>());
    SDL_Color textColor = Widget::ParseVar("text_color", conf, root->GetVars());
    std::vector<std::string> tarr = conf->Get("text_arr").get<std::vector<std::string>>();

    MultiItemsProp prop = {
                        dimr,
                        font,
                        tarr,
                        textColor,
                        backgroundColor,
                        borderColor
                    };
    return prop;
}