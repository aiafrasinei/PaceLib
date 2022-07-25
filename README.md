# PaceLib

Features:
- 2d c++ graphics library (based on SDL2).
- Easy to use
- Flexible widget system (json configuration or code).
- Designed for 2d games (focus on point and click)
- Examples
(https://github.com/aiafrasinei/PaceLib/tree/main/examples)
- Good documentation

Prerequisites:
- SDL2 for rendering
- SDL_ttf 
- c++20 compiler
- cmake

Code:

After the PaceLib initialization

    Text::Create("title_txt");
    Button::Create("new_btn");
    
In the wconfs folder the corresponding json configurations:

    title_txt.wconf:

    {
        "scene" : "Default",
        "font" : "font_title",
        "text" : "Game",
        "pos" : ["W_2%", "H_1%"],
        "text_color" : [140, 190, 140, 255]
    }

    new_btn.wconf:

    {
        "dim" : ["W_2%", "H_10%", "W_7.5%", "H_3%"],
        "color" : [40, 40, 40, 255],
        "scene" : "Default",
        "font" : "default",
        "text" : "New",
        "text_color" : [140, 170, 140, 255],
        "align" : ["mid", "mid"]
    }

The other option is to use code.
