#include "FontContainer.hpp"
#include "ConLog.hpp"
#include "core/Window.hpp"

using namespace PaceLib;


FontContainer::FontContainer(std::string name)
{
    this->name = name;
}

FontContainer::~FontContainer()
{
    for (auto const& pair : fnm) {
        if(pair.second != nullptr) {
            FC_FreeFont(pair.second);
        }
    }
    fnm.clear();
}

std::string FontContainer::GetName()
{
    return name;
}

void FontContainer::ChangeName(std::string name)
{
    this->name = name;
}

FC_Font *FontContainer::Get(std::string name)
{
   return fnm[name];
}

void FontContainer::Remove(std::string name)
{
    FC_FreeFont(fnm[name]);
    fnm.erase(name);
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
        fnm[name] = font;

        ConLog::Info("Loaded font " + name + " filepath: " + file_path.filename().string());
    }

    return true;
}
