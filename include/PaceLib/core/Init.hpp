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

            std::function<void(void)> onInit;
            std::function<void(void)> onDeinit;
    };
}