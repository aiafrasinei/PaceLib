#pragma once

#include "Widget.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"
#include "../core/interfaces/Updateable.hpp"
#include <functional>


namespace PaceLib
{

    class ComboBox : public Widget
    {
        public:

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "dim" : ["W_47%", "H_23%", "H_7.5%", "H_3%"],
                "color" : [100, 100, 70, 255],
                "scene" : "Default",
                "font" : "default",
                "text" : "Start",
                "text_color" : [0, 0, 0, 255],
                "items" : ["test1", "test2", "test3", "test4", "test5"]
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            //used when the button will have child elements
            static void BeginBlock(std::string name);
            static void EndBlock();

// programmatic
            static void Begin(ShapeId sid, PropDimColor dco, PropFontText fto);

            ~ComboBox();

            void Draw();
            void Update(SDL_Event *e);
            
            std::function<void(void)> onClickCallback;

            int GetSelected();
            int GetNrItems();

            void AddItem(std::string item);
            void AddItems(std::vector<std::string> items);
            void ReplaceItems(std::vector<std::string> items);
            
        private:
            ComboBox(ShapeId sid, PropDimColor dco, PropFontText fto);

            SDL_Color textColor;

            Align align;
            
            bool mouseOver;

            bool highlight;

            SDL_Color highlightColor;

            SDL_Texture *tex;

            std::string text;

            int textSize;

            PropFontText fto;

            void InternalInit();

            std::vector<std::string> items;

            int selected;

            bool mainRendererSelected;
    };
}