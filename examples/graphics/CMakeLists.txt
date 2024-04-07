cmake_minimum_required(VERSION 3.5)

project(graphics)


include_directories(source)

set(LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}../../libs")
set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../include")
set(PACE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../include/PaceLib")

include_directories("${INCLUDE_PATH}")
include_directories("${PACE_INCLUDE_PATH}")
include_directories("${PACE_INCLUDE_PATH}/utils")
include_directories("${PACE_INCLUDE_PATH}/config")
include_directories("${PACE_INCLUDE_PATH}/core")
include_directories("${PACE_INCLUDE_PATH}/graphics")
include_directories("${PACE_INCLUDE_PATH}/graphics/lines")
include_directories("${PACE_INCLUDE_PATH}/graphics/effects")
include_directories("${PACE_INCLUDE_PATH}/graphics/polygons")
include_directories("${PACE_INCLUDE_PATH}/graphics/polygons/quads")
include_directories("${PACE_INCLUDE_PATH}/graphics/gui")
include_directories("${PACE_INCLUDE_PATH}/graphics/conics")
include_directories("${PACE_INCLUDE_PATH}/resources")
include_directories("${PACE_INCLUDE_PATH}/scene")

IF(UNIX)
    #set(CMAKE_CXX_FLAGS "-std=c++23 -fanalyzer")
    set(CMAKE_CXX_FLAGS "-std=c++23")

    include_directories("/opt/homebrew/include")

    link_directories("${LIBS_PATH}/unix/SDL2/")
    link_directories("${LIBS_PATH}/unix/SDL2_image/")
    link_directories("${LIBS_PATH}/unix/SDL2_ttf/")

    link_directories("/opt/homebrew/lib/")
    link_directories("/usr/local/lib64/")

    add_executable (graphics
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
            ../../src/Lines.cpp
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
            ../../src/Texture.cpp
            ../../src/Configuration.cpp)

    target_link_libraries(graphics m dl SDL3 SDL3_image SDL3_ttf)

ELSE (WIN32)
    include_directories("${LIBS_PATH}/windows/SDL2/include")
    include_directories("${LIBS_PATH}/windows/SDL2_image/include")
    include_directories("${LIBS_PATH}/windows/SDL2_ttf/include")

    link_directories("${LIBS_PATH}/windows/SDL2/lib/x64")
    link_directories("${LIBS_PATH}/windows/SDL2_image/lib/x64")
    link_directories("${LIBS_PATH}/windows/SDL2_ttf/lib/x64")

    add_executable (graphics
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
        ../../src/Lines.cpp
        ../../src/Triangle.cpp
        ../../src/Polygon.cpp
        ../../src/ScrollingBackground.cpp
        ../../src/Tex.cpp
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
        ../../src/Texture.cpp
        ../../src/Configuration.cpp)

    target_link_libraries(graphics SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib)

ENDIF (UNIX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
