cmake_minimum_required(VERSION 3.5)

project(boards)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(source)

set(LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}../../libs")
set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../include")
set(PACE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../include/PaceLib")

include_directories("${INCLUDE_PATH}")
include_directories("${PACE_INCLUDE_PATH}")
include_directories("${PACE_INCLUDE_PATH}/utils")
include_directories("${PACE_INCLUDE_PATH}/utils/sqlite3")
include_directories("${PACE_INCLUDE_PATH}/utils/sqlht")
include_directories("${PACE_INCLUDE_PATH}/utils/SDL2")
include_directories("${PACE_INCLUDE_PATH}/config")
include_directories("${PACE_INCLUDE_PATH}/core")
include_directories("${PACE_INCLUDE_PATH}/graphics")
include_directories("${PACE_INCLUDE_PATH}/graphics/effects")
include_directories("${PACE_INCLUDE_PATH}/graphics/polygons")
include_directories("${PACE_INCLUDE_PATH}/graphics/polygons/quads")
include_directories("${PACE_INCLUDE_PATH}/graphics/conics")
include_directories("${PACE_INCLUDE_PATH}/graphics/lines")
include_directories("${PACE_INCLUDE_PATH}/graphics/gui")
include_directories("${PACE_INCLUDE_PATH}/resources")
include_directories("${PACE_INCLUDE_PATH}/scene")

IF(UNIX)
    include_directories("/opt/homebrew/include")

    link_directories("${LIBS_PATH}/unix/SDL2/")
    link_directories("${LIBS_PATH}/unix/SDL2_image/")
    link_directories("${LIBS_PATH}/unix/SDL2_ttf/")

    link_directories("/opt/homebrew/lib/")

    add_executable (boards
            src/main.cpp
            ../../src/Window.cpp
            ../../src/Init.cpp
            ../../src/Scene.cpp
            ../../src/TexContainer.cpp
            ../../src/Place.cpp
            ../../src/Map.cpp
            ../../src/Rectangle.cpp
            ../../src/Sprite.cpp
            ../../src/Text.cpp
            ../../src/Circle.cpp
            ../../src/Line.cpp
            ../../src/Triangle.cpp
            ../../src/Polygon.cpp
            ../../src/ScrollingBackground.cpp
            ../../src/FontContainer.cpp
            ../../src/SDL_FontCache.cpp
            ../../src/Timer.cpp
            ../../src/Label.cpp
            ../../src/Button.cpp
            ../../src/ButtonTex.cpp
            ../../src/CheckBox.cpp
            ../../src/Tab.cpp
	        ../../src/Root.cpp
            ../../src/Tooltip.cpp
            ../../src/TextArea.cpp
            ../../src/TextInput.cpp
            ../../src/Tabber.cpp
            ../../src/Configuration.cpp
            ../../src/ComboBox.cpp
            ../../src/Hotspot.cpp)

    target_link_libraries(boards m dl SDL2 SDL2_image SDL2_ttf pthread)

ELSE (WIN32)
    include_directories("${LIBS_PATH}/windows/SDL2/include")
    include_directories("${LIBS_PATH}/windows/SDL2_image/include")
    include_directories("${LIBS_PATH}/windows/SDL2_ttf/include")

    link_directories("${LIBS_PATH}/windows/SDL2/lib/x64")
    link_directories("${LIBS_PATH}/windows/SDL2_image/lib/x64")
    link_directories("${LIBS_PATH}/windows/SDL2_ttf/lib/x64")

    add_executable (boards 
            src/main.cpp
            ../../src/Window.cpp
            ../../src/Init.cpp
            ../../src/Scene.cpp
            ../../src/TexContainer.cpp
            ../../src/Place.cpp
            ../../src/Map.cpp
            ../../src/Rectangle.cpp
            ../../src/Sprite.cpp
            ../../src/Text.cpp
            ../../src/Circle.cpp
            ../../src/Line.cpp
            ../../src/Triangle.cpp
            ../../src/Pentagon.cpp
            ../../src/Hexagon.cpp
            ../../src/Polygon.cpp
            ../../src/ScrollingBackground.cpp
            ../../src/FontContainer.cpp
            ../../src/SDL_FontCache.cpp
            ../../src/Timer.cpp
            ../../src/Label.cpp
            ../../src/Button.cpp
            ../../src/ButtonTex.cpp
            ../../src/CheckBox.cpp
            ../../src/Tab.cpp
	        ../../src/Root.cpp
            ../../src/Tooltip.cpp
            ../../src/TextArea.cpp
            ../../src/TextInput.cpp
            ../../src/Tabber.cpp
            ../../src/Configuration.cpp
            ../../src/ComboBox.cpp
            ../../src/Hotspot.cpp)

    target_link_libraries(boards SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib)

ENDIF (UNIX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
