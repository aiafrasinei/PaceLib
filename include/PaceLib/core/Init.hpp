#pragma once

#include "PaceLib.h"


namespace PaceLib
{
    class Init
    {
        private:
            Configuration* conf;
            Window *win;
            Root *root;

        public:
            Init();
            ~Init();

            void Loop();
            Root *GetRoot();
            Window *GetWindow();

            std::function<void(void)> onInit = nullptr;
            std::function<void(void)> onDeinit = nullptr;
            std::function<void(void)> onDraw = nullptr;
            std::function<void(void)> onUpdate = nullptr;
            std::function<void(SDL_Event *)> onEvent = nullptr;
    };
}