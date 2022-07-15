#pragma once

#define PACE_LIB_VERSION_MAJOR 0
#define PACE_LIB_VERSION_MINOR 1
#define PACE_LIB_VERSION_PATCH 1

//core
#include "core/Window.h"

//resources
#include "resources/FontContainer.h"

//utils
#include "config/version.h"
#include "config/Configuration.h"
#include "utils/ConLog.h"
#include "utils/SDL2/SDL_FontCache.h"
#include "utils/SDL2/SDL2_framerate.h"
#include "utils/SDL2/SDL2_rotozoom.h"
#include "utils/SDL2/SDL2_imageFilter.h"
#include "utils/Timer.h"
#include "utils/Random.h"
#include "utils/Scale.h"

//scenes
#include "scene/Map.h"
#include "scene/Scene.h"

//shapes
#include "graphics/Shape.h"

#include "graphics/Line.h"
#include "graphics/VerticalLine.h"
#include "graphics/HorizontalLine.h"

#include "graphics/Circle.h"
#include "graphics/Ellipse.h"

#include "graphics/Sprite.h"

//polygons
#include "graphics/polygons/Polygon.h"
#include "graphics/polygons/Rectangle.h"
#include "graphics/polygons/Triangle.h"
#include "graphics/polygons/Pentagon.h"
#include "graphics/polygons/Hexagon.h"

//gui
#include "graphics/gui/Root.h"
#include "graphics/gui/Tab.h"
#include "graphics/gui/Label.h"
#include "graphics/gui/Button.h"
#include "graphics/gui/ButtonTex.h"
#include "graphics/gui/CheckBox.h"
#include "graphics/gui/TextArea.h"
#include "graphics/gui/Tooltip.h"
#include "graphics/gui/TextInput.h"
#include "graphics/gui/Tabber.h"
#include "graphics/gui/Texture.h"


//effects
#include "graphics/effects/ScrollingBackground.h"

//text
#include "graphics/Text.h"

