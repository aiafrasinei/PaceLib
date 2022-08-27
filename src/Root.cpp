#include "Root.h"

using namespace PaceLib;


Root::Root()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;

    color.r = Window::GetBackgroundColor().r;
    color.g = Window::GetBackgroundColor().g;
    color.b = Window::GetBackgroundColor().b;
    color.a = Window::GetBackgroundColor().a;

    hidden = false;

    rtype = DrawTypes::OUTLINE;
    name = "root";

    scenes.push_back(std::move(new Scene("Default", Window::GetWindow(), Window::GetRenderer())));
    scenes[0]->GetFontContainer()->Add("default", "fonts/OpenSans_Condensed-Regular.ttf", 20, 0, 0, 0, 255);

    wtype = WidgetType::ROOT;
}

Root::~Root()
{
    for(int i=0; i < scenes.size(); i++) {
        delete scenes[i];
        scenes.clear();
    }
}

void Root::Draw()
{
    SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);

    if(this->state != nullptr) {
        this->state->Loop();
    }

    for(Shape *w : shapes) {
        w->Draw();
    }

    

    SDL_SetRenderDrawColor(Window::GetRenderer(), Window::GetBackgroundColor().r, Window::GetBackgroundColor().g, Window::GetBackgroundColor().b,  Window::GetBackgroundColor().a);
}

void Root::Add(Shape *s)
{
    shapes.push_back(s);
}


Button *Root::GetButton(std::string child)
{
    return static_cast<Button *>(this->Get(child));
}

ButtonTex *Root::GetButtonTex(std::string child)
{
    return static_cast<ButtonTex *>(this->Get(child));
}

Label *Root::GetLabel(std::string child)
{
    return static_cast<Label *>(this->Get(child));
}

Widget *Root::GetWidget(std::string child)
{
    return static_cast<Widget *>(this->Get(child));
}

Tab *Root::GetTab(std::string child)
{
    return static_cast<Tab *>(this->Get(child));
}

Tabber *Root::GetTabber(std::string child)
{
    return static_cast<Tabber *>(this->Get(child));
}

Hotspot *Root::GetHotspot(std::string child)
{
    return static_cast<Hotspot *>(this->Get(child));
}


Text *Root::GetText(std::string child)
{
    return static_cast<Text *>(this->Get(child));
}

Tooltip *Root::GetTooltip(std::string child)
{
    return static_cast<Tooltip *>(this->Get(child));
}

DefaultTooltip *Root::GetDefaultTooltip(std::string child)
{
    return static_cast<DefaultTooltip *>(this->Get(child));
}

CheckBox *Root::GetCheckBox(std::string child)
{
    return static_cast<CheckBox *>(this->Get(child));
}

TextInput *Root::GetTextInput(std::string child)
{
    return static_cast<TextInput *>(this->Get(child));
}

TextArea *Root::GetTextArea(std::string child)
{
    return static_cast<TextArea *>(this->Get(child));
}

void Root::Update(SDL_Event *e)
{
    for(Shape *s : shapes) {
        s->Update(e);
    }
}

void Root::SetState(State *state)
{
    this->state = state;
    this->state->Execute();
}

std::vector<Scene *> Root::GetScenes()
{
    return scenes;
}

Scene *Root::GetScene(int index)
{
    return scenes[index];
}

Scene *Root::GetScene(std::string name)
{
    for(int i=0; i<scenes.size(); i++) {
        if(scenes[i]->GetName() == name) {
            return scenes[i];
        }
    }
}

void Root::HideAll()
{
    for(Shape *s : shapes) {
        s->Hide();
    }
}