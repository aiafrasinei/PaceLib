#include "FontContainer.h"
#include "ConLog.h"
#include "core/Window.h"

using namespace PaceLib;


FontContainer::FontContainer(std::string name)
{
    this->name = name;
}

FontContainer::~FontContainer()
{

}

std::string FontContainer::GetName()
{
    return name;
}

void FontContainer::ChangeName(std::string name)
{
    this->name = name;
}

FC_Font *FontContainer::Get(long index)
{
    return fonts[index];
}

FC_Font *FontContainer::Get(std::string name)
{
    for(int i=0; i<fonts_names.size(); i++) {
        if(fonts_names[i] == name) {
            return fonts[i];
        }        
    }
    
    return NULL;
}

bool FontContainer::Remove(long index)
{
    if(index >= fonts.size()) {
        return false;
    }

    FC_FreeFont(fonts[index]);
    fonts[index] = NULL;
    fonts.erase(fonts.begin() + index);

    return true;
}

bool FontContainer::Remove(std::string name)
{
    for(int i=0; i<fonts_names.size(); i++) {
        if(fonts_names[i] == name) {
            Remove(i);

            return true;
        }        
    }

    return false;
}

bool FontContainer::Add(std::string name, std::filesystem::path file_path, int size, int r, int g, int b, int a)
{
    FC_Font* font = FC_CreateFont();

    int ret=FC_LoadFont(font, Window::GetRenderer(), file_path.string().c_str(), size, FC_MakeColor(r,g,b,a), TTF_STYLE_NORMAL);
    
    if(ret != 0)
    {
        printf( "Failed to load font");
        return false;
    }
    else
    {
        fonts.push_back(font);
        fonts_names.push_back(name);

        ConLog::Info("Loaded font " + name + " filepath: " + file_path.filename().string());
    }

    return true;
}
