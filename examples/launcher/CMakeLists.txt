cmake_minimum_required(VERSION 3.5)

project(launcher)
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

set(CMAKE_CXX_FLAGS "-std=c++20")

include_directories("/opt/homebrew/include")
include_directories("/mingw64/include/")

link_directories("/opt/homebrew/lib/")
link_directories("/usr/local/lib64/")
link_directories("/mingw64/lib/")

add_executable (launcher
        src/main.cpp
        ../../src/Window.cpp
        ../../src/Init.cpp
        ../../src/Scene.cpp
        ../../src/TexContainer.cpp
        ../../src/TtfContainer.cpp
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
        ../../src/Hotspot.cpp
        ../../src/Grid.cpp
        ../../src/ButtonTexGrid.cpp)

target_link_libraries(launcher m dl SDL2 SDL2_image SDL2_ttf pthread)

set(CMAKE_BUILD_TYPE Debug)
