# PaceLib 1.1.3

Features:

- Open source 2d c++ graphics library (based on SDL3)
- Easy to use!
- Flexible widget system (json configuration or code)
- Widgets (label, button, tooltip, checkbox, combobox, textinput, textarea, tabber, tab)
- Custom widgets are easy to add
- Designed for 2d games
- Works on Linux/Windows/MacOS
- Examples and good documentation

Prerequisites:

- c++20 compiler
- SDL3, SDL_image, SDL_ttf
- cmake

Documentation:

- [Install](https://github.com/aiafrasinei/PaceLib/blob/main/INSTALL.md)
- [Examples](https://github.com/aiafrasinei/PaceLib/tree/main/examples)
- [Code documentation](https://binary-station.github.io/PaceLib/html/index.html)

Helper projects:

- [PaceLibReleaseTool](https://github.com/aiafrasinei/PaceLibReleaseTool) (Create releases for PaceLib)
- [PaceLibTemplateProject](https://github.com/aiafrasinei/PaceLibTemplateProject) (Example how to setup a project)

Screenshots:

- [Screenshots](https://github.com/aiafrasinei/PaceLib/blob/main/SCREENSHOTS.md)

Code:

After the PaceLib initialization

    Text::Create("title");
    Button::Create("new");
    
In the wconfs folder the corresponding json configurations:

    title_Text.wconf:

	{
	    "scene" : "Default",
	    "pos" : ["W_1%", "W_0.6%"],
	    "font" : "default",
	    "text" : "Text text text",
	    "color" : [140, 140, 140, 255]
	}

    new_Button.wconf:

	{
	    "scene" : "Default",
	    "rect" : ["H_82%", "H_11%", "W_7.5%", "H_3%"],
	    "font" : "default",
	    "text" : "Start",
	    "text_color" : "$TEXT",
	    "align" : "mid",
	    "background" : "$BACKGROUND",
	    "highlight" : "$HIGHLIGHT",
	    "border" : "$BORDER"
	}
	
    vars file:
    
	{
	    "BACKGROUND" : [100, 100, 100, 255],
	    "BORDER" : [0, 0, 0, 255],
	    "HIGHLIGHT" : [120, 120, 120, 255],
	    "TEXT" : [0, 0, 0, 255]
	}
	
    Variables that can be use in the other wconf files
    "highlight" : "$HIGHLIGHT", will be replaced with [120, 120, 120, 255]
    
Widgets can have child elements example:

    Tab::BeginBlock("second_tab");
		Text::Begin("text");
		Label::BeginBlock("out_lbl");
			DefaultTooltip::Begin("out_tooltip");
		Label::EndBlock();
		TextArea::Begin("text_ta");
		TextInput::Begin("tinput");
		CheckBox::Begin("cb");
	Tab::EndBlock();
    
Event handling:

    Tab::BeginBlock("first_tab");
		Label::Begin("label_lbl");
		Button::Begin("start_btn");
		Button::Begin("exit");
	Tab::EndBlock();
	
	root->GetTab("first_tab")->GetButton("exit")->mouseLeftButtonUpCallback = []() {
		Window::running = false;
    };
   
The other option is to use code:

    TextProp prop = {600, 100, root->GetScene("Default")->GetFont("lazy_font"),
		        "some text", {0, 0, 0, 255}};
    Text::Begin({root, "text"}, prop);

Limitations:

Not designed for complex desktop applications (just games)

Doesn't take care of different aspect ratios for widgets

(has the tools but you need to do manually)

 <br>

Enjoy!
