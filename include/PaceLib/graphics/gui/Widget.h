#pragma once

#include "Shape.h"
#include "Props.h"
#include <map>


namespace PaceLib
{

    class Widget : public Shape
    {
        public:
            virtual void Draw() = 0;

            void SetRect(float x, float y, float w , float h)
            {
                rect.x = x;
                rect.y = y;
                rect.w = w;
                rect.h = h;
            }

            void SetRect(SDL_Rect rect)
            {
                this->rect.x = rect.x;
                this->rect.y = rect.y;
                this->rect.w = rect.w;
                this->rect.h = rect.h;
            }

            void SetRectX(float x)
            {
                rect.x = x;
            }

            void SetRectY(float y)
            {
                rect.y = y;
            }

            void SetRectW(float w)
            {
                rect.w = w;
            }

            void SetRectH(float h)
            {
                rect.h = h;
            }


            SDL_Rect GetRect()
            {
                return rect;
            }

            float GetHalfX() { return rect.x + rect.w/2; }
            float GetHalfY() { return rect.y + rect.h/2; }

            void SetBorderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
            {
                borderColor.r = r;
                borderColor.g = g;
                borderColor.b = b;
                borderColor.a = a;
            }

            bool PointInRect(SDL_Point p, SDL_Rect r) {
                return ( (p.x >= r.x) && (p.x < (r.x + r.w)) &&
                    (p.y >= r.y) && (p.y < (r.y + r.h)) ) ? true : false;
            }

            WidgetType GetWidgetType() {
                return wtype;
            }

            static void ParseDim(int dim[4], Configuration *conf) {
                for(int i=0; i<4; i++) {
                    std::string str = conf->Get("dim")[i].get<std::string>();
                    std::string first_char = str.substr(0,1);

                    float val = 0;
                    if(str == "W") {
                        val = Window::width;
                    } else if(str == "H") {
                        val = Window::height;
                    } else if(first_char == "W" || first_char == "H") {
                        std::size_t pos = str.find("%");
                        if (pos != std::string::npos) {
                            if(first_char == "W")
                                val = Window::width*std::stoi(str.substr(2,pos))/100;
                            if(first_char == "H")
                                val = Window::height*std::stoi(str.substr(2,pos))/100;
                        }
                    } else {
                        val = std::stof(str);
                    }

                    dim[i] = val;
                }
            }

            static void ParsePos(int pos[2], Configuration *conf) {
                for(int i=0; i<2; i++) {
                    std::string str = conf->Get("pos")[i].get<std::string>();
                    std::string first_char = str.substr(0,1);

                    float val = 0;
                    if(str == "W") {
                        val = Window::width;
                    } else if(str == "H") {
                        val = Window::height;
                    } else if(first_char == "W" || first_char == "H") {
                        std::size_t pos = str.find("%");
                        if (pos != std::string::npos) {
                            if(first_char == "W")
                                val = Window::width*std::stoi(str.substr(2,pos))/100;
                            if(first_char == "H")
                                val = Window::height*std::stoi(str.substr(2,pos))/100;
                        }
                    } else {
                        val = std::stof(str);
                    }

                    pos[i] = val;
                }
            }

            static SDL_Color ParseVar(std::string key, Configuration *conf, Configuration *vars) {
                SDL_Color color;

                if(conf->Get(key).is_string()) {
                    std::string name = conf->Get(key).get<std::string>().substr(1);
                    if(vars->Get(name) != nullptr) {
                        color = {vars->Get(name)[0], vars->Get(name)[1], vars->Get(name)[2], vars->Get(name)[3]};
                    }
                } else {
                    color = {conf->Get(key)[0], conf->Get(key)[1], conf->Get(key)[2], conf->Get(key)[3]};
                }
                
                return color;
            }
        protected:
            SDL_Rect rect = {0, 0, 0, 0};

            SDL_Color borderColor;

            WidgetType wtype;
    };

    struct ShapeId
    {
         Shape *parent;
         std::string name;
    };
}