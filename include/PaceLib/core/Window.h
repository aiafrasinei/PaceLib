#pragma once

#include "../utils/sdlu.h"
#include "../config/Configuration.h"


class Window
{

public:
    Window(Configuration *conf);
    ~Window();
    
    static SDL_Renderer *GetRenderer();
    static SDL_Window *GetWindow();

    void Clear();
    void Present();
    void Close();

    static void SetDrawColor(SDL_Color col);
    static void SetDrawColor(int r, int g, int b, int a);

    static void SetBackgroundColor(SDL_Color col);
    static void SetBackgroundColor(int r, int g, int b, int a);

    static SDL_Color GetBackgroundColor();

    static bool running;

    static int width, height;

private:
    static SDL_Renderer* renderer;
    static SDL_Window* window;

    static SDL_Color backgroundColor;

    bool success;

protected:

};