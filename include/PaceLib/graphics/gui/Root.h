#pragma once

#include "Widget.h"
#include "Button.h"
#include "ButtonTex.h"
#include "Label.h"
#include "Tab.h"
#include "Tabber.h"
#include "Hotspot.h"
#include "Tooltip.h"
#include "CheckBox.h"
#include "TextInput.h"
#include "TextArea.h"
#include "resources/FontContainer.hpp"
#include "scene/Scene.hpp"
#include "core/interfaces/State.hpp"


namespace PaceLib
{

    class Root : public Widget
    {
        public:
            ~Root();

            static Root& GetInstance() {
                static Root instance;
                return instance;
            }

            static Shape *GetCurrent() {
                return GetInstance().current;
            }

            static void SetCurrent(Shape *w) {
                GetInstance().current = w;
            }

            void Draw();

            void Add(Shape *s);

            void Update(SDL_Event *e);

            std::map<std::string, Scene *> GetScenes();
            Scene *GetScene(std::string name);
            void AddScene(std::string name);
            void RemoveScene(std::string name);

            Button *GetButton(std::string child);
            ButtonTex *GetButtonTex(std::string child);
            Label *GetLabel(std::string child);
            Tab *GetTab(std::string child);
            Widget *GetWidget(std::string child);
            Tabber *GetTabber(std::string child);
            Hotspot *GetHotspot(std::string child);
            Text *GetText(std::string child);
            Tooltip *GetTooltip(std::string child);
            DefaultTooltip *GetDefaultTooltip(std::string child);
            CheckBox *GetCheckBox(std::string child);
            TextInput *GetTextInput(std::string child);
            TextArea *GetTextArea(std::string child);

            void SetState(State *state);
            void HideAll();

        private:
            State *state;

            std::map<std::string, Scene *> scenes;

            Root();
    };

}