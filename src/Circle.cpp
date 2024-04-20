#include "graphics/conics/Circle.hpp"
#include "Root.hpp"
#include "Window.hpp"

using namespace PaceLib;

Circle::Circle(ShapeId sid, CircleProp prop) {
  this->prop = prop;

  if (sid.parent->name != "root") {
    this->prop.x = sid.parent->GetRect().x + prop.x;
    this->prop.y = sid.parent->GetRect().y + prop.y;
  }

  hidden = false;

  rtype = DrawTypes::OUTLINE;

  this->name = sid.name;
}

Circle::~Circle() {}

void Circle::SetDrawType(DrawTypes rtype) { this->rtype = rtype; }

void Circle::Begin(ShapeId sid) {
  std::string path = "wconfs/" + sid.name + "_Circle.conf";
  if (std::filesystem::exists(path)) {
    Configuration *conf = new Configuration(path);

    float x = conf->Get("x");
    float y = conf->Get("y");
    float radius = conf->Get("radius");
    SDL_FColor color = {conf->Get("color")[0], conf->Get("color")[1],
                       conf->Get("color")[2], conf->Get("color")[3]};

    sid.parent->Add(new Circle(sid, {x, y, radius, color}));
  }
}

void Circle::Begin(std::string name) {
  Root *root = &Root::GetInstance();
  Circle::Begin({root->GetCurrent(), name});
}

void Circle::BeginBlock(std::string name) {
  Root *root = &Root::GetInstance();
  Circle::Begin({root->GetCurrent(), name});

  Shape *prevParent = root->GetCurrent();
  root->SetCurrent(root->GetCurrent()->Get(name));
  root->GetCurrent()->SetParent(prevParent);
}

void Circle::EndBlock() {
  Root *root = &Root::GetInstance();
  root->SetCurrent(root->GetCurrent()->GetParent());
}

void Circle::Begin(ShapeId sid, CircleProp prop) {
  sid.parent->Add(new Circle(sid, prop));
}

void Circle::Draw() {
  if (!hidden) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), prop.color.r, prop.color.g,
                           prop.color.b, prop.color.a);

    if (rtype == DrawTypes::OUTLINE) {
      int offsetx, offsety, d;
      int status;

      offsetx = 0;
      offsety = prop.radius;
      d = prop.radius - 1;
      status = 0;

      while (offsety >= offsetx) {
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x + offsetx,
                                      prop.y + offsety);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x + offsety,
                                      prop.y + offsetx);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x - offsetx,
                                      prop.y + offsety);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x - offsety,
                                      prop.y + offsetx);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x + offsetx,
                                      prop.y - offsety);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x + offsety,
                                      prop.y - offsetx);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x - offsetx,
                                      prop.y - offsety);
        status += SDL_RenderPoint(Window::GetRenderer(), prop.x - offsety,
                                      prop.y - offsetx);

        if (status < 0) {
          break;
        }

        if (d >= 2 * offsetx) {
          d -= 2 * offsetx + 1;
          offsetx += 1;
        } else if (d < 2 * (prop.radius - offsety)) {
          d += 2 * offsety - 1;
          offsety -= 1;
        } else {
          d += 2 * (offsety - offsetx - 1);
          offsety -= 1;
          offsetx += 1;
        }
      }
    } else if (rtype == DrawTypes::FILLED) {
      int offsetx, offsety, d;
      int status;

      offsetx = 0;
      offsety = prop.radius;
      d = prop.radius - 1;
      status = 0;

      while (offsety >= offsetx) {

        status += SDL_RenderLine(Window::GetRenderer(), prop.x - offsety,
                                     prop.y + offsetx, prop.x + offsety,
                                     prop.y + offsetx);
        status += SDL_RenderLine(Window::GetRenderer(), prop.x - offsetx,
                                     prop.y + offsety, prop.x + offsetx,
                                     prop.y + offsety);
        status += SDL_RenderLine(Window::GetRenderer(), prop.x - offsetx,
                                     prop.y - offsety, prop.x + offsetx,
                                     prop.y - offsety);
        status += SDL_RenderLine(Window::GetRenderer(), prop.x - offsety,
                                     prop.y - offsetx, prop.x + offsety,
                                     prop.y - offsetx);

        if (status < 0) {
          break;
        }

        if (d >= 2 * offsetx) {
          d -= 2 * offsetx + 1;
          offsetx += 1;
        } else if (d < 2 * (prop.radius - offsety)) {
          d += 2 * offsety - 1;
          offsety -= 1;
        } else {
          d += 2 * (offsety - offsetx - 1);
          offsety -= 1;
          offsetx += 1;
        }
      }
    }
  }
}
