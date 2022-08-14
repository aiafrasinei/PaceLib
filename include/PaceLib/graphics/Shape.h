#pragma once

#include <string>
#include <vector>
#include "../utils/sdlu.h"
#include "../utils/DrawTypes.h"
#include "../core/interfaces/Drawable.h"
#include "../core/interfaces/Hidable.h"
#include "../core/interfaces/Updateable.h"
#include "../core/Window.h"


namespace PaceLib
{

    class Shape : public Drawable , public Hidable, public Updateable
    {
    public:
        Shape()
        {
            hidden = false;
            conf = nullptr;
        }

        ~Shape()
        {

        }
        
        void DrawRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
            SDL_SetRenderDrawColor(Window::GetRenderer(), r, g, b, a);
            Draw();
        }

        std::string name;
        std::vector<std::string> shapesNames;
        std::vector<Shape *> shapes;

        std::vector<Shape *> Get()
        {
            return shapes;
        }

        Shape *Get(int index)
        {
            return shapes[index];
        }

        Shape *Get(std::string name)
        {
            for(int i=0; i<shapesNames.size(); i++) {
                if (shapesNames[i] == name) {
                    return shapes[i];
                }
            }

            return nullptr;
        }

        void Add(Shape *s)
        {
            shapes.push_back(std::move(s));
            shapesNames.push_back(s->name);
        }

        long GetNr()
        {
            return shapes.size();
        }

        void SetDrawType(DrawTypes rtype)
        {
            this->rtype = rtype;
        }

        void SetParent(Shape *p)
        {
            this->parent = p;
        }

        Shape *GetParent()
        {
            return this->parent;
        }

        void Update(SDL_Event *e)
        {

        }

        SDL_Color GetColor()
        {
            return color;
        }

        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        } 

        void SetColor(SDL_Color col)
        {
            color.r = col.r;
            color.g = col.g;
            color.b = col.b;
            color.a = col.a;
        }

        Configuration *conf;
    protected:
 
        void LoadDrawColor()
        {
            Uint8 dr, dg, db, da;

            SDL_GetRenderDrawColor(Window::GetRenderer() , &dr, &dg, &db, &da);

            SetColor(dr, dg, db, da);
        }

        DrawTypes rtype;

        Shape *current;

        Shape *parent;
        
    private:

    };

}
