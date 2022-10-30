#pragma once

#include "Widget.h"
#include "Button.h"
#include "Tab.h"
#include "../../utils/SDL2/SDL_FontCache.h"
#include "Text.h"


namespace PaceLib
{

    class Tabber : public Widget
    {
        public:

//static methods

// json configuration

            /* Loads wconf file
            example format:
            {
                "scene" : "Default",
                "dim" : ["W_3%", "W_30%", "W_19%", "W_19%"],
                "background_color" : [70, 80, 70, 255],
                "border_color" : "$BORDER",
                "header_background_color" : [120, 120, 120, 255]
                "tab_background_color" : [120, 120, 120, 255]
                "tab_border_color" : [120, 120, 120, 255]
                "buttons_font" : "default",
                "buttons_text_color" : "$TEXT",
                "buttons_text_align" : "left",
                "buttons_background_color" : "$BACKGROUND",
                "buttons_border_color" : "$BORDER",
                "buttons_highlight_color" : "$HIGHLIGHT"
            }*/
            static void Begin(ShapeId sid);
            static void Begin(std::string name);

            static void BeginBlock(std::string name);
            static void EndBlock();

            static void BeginTabBlock(std::string text);
            static void EndTabBlock();

// programmatic

            static void Begin(ShapeId sid, TabberProp prop);

//end static methods

            void SetTextColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void Draw();

            void AddTab(std::string text);
            void AddTab(std::string name, std::string text);

            TabberProp GetProp();

            void Update(SDL_Event *e);

            ~Tabber();
            
        private:
            std::vector<std::string> titles;

            SDL_Color textColor;

            int bcounter;

            SDL_Rect top;

            static unsigned int current;
            static int tabx;

            TabberProp prop;

            static TabberProp LoadTabberProp(Configuration *conf);

            Tabber(ShapeId sid, TabberProp prop);
    };

}