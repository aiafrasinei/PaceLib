#pragma once

#include <SDL2/SDL.h>
#include "../utils/SDL2/SDL_FontCache.h"
#include <string>

namespace PaceLib
{

    enum class H
    {
        LEFT,
        MID,
        RIGHT
    };

    enum class V
    {
        TOP,
        MID,
        BOTTOM
    };

    enum class WidgetType
    {
        ROOT,
        TAB,
        TABBER,
        LABEL,
        BUTTON,
        BUTTONTEX,
        HOTSPOT,
        TOOLTIP,
        TEXTINPUT,
        TEXTAREA,
        CHECKBOX,
        TEXTURE,
        CUSTOM
    };

    struct Align
    {
        V valign;
        H halign;
    };

    struct PropDimColor
    {
        SDL_Rect rect;
        SDL_Color color;
    };

    struct PropFontText
    {
        FC_Font *font;
        std::string text;
    };
    
    struct PropTex
    {
        SDL_Texture *tex;
        SDL_Rect rect;
    };

    struct ButtonProp
    {
        SDL_Rect rect;
        SDL_Color backgroundColor;
        SDL_Color highlightColor;
        SDL_Color borderColor;
        FC_Font *font;
        std::string text;
        SDL_Color textColor;
        Align align;
    };
}