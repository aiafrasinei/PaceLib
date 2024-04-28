How to install

***

This is the recommended way to use PaceLib.

Prerequisites:
- c++23 compiler
- SDL2, SDL2_image, SDL2_ttf 
- cmake

Until SDL3 is released:

https://github.com/libsdl-org

Build from source with cmake and make install.

**Linux**:

Install the prerequisites using you own distro install system.

fedora:

    dnf install SDL2 SDL2-devel SDL2_image SDL2_image-devel SDL2_ttf SDL2_ttf-devel

ubuntu:

    apt install libsdl libsdl2-dev libsdl2_image libsdl2_image-dev libsdl2_ttf libsdl2_ttf-dev

**Windows**:

Install msys2

https://www.msys2.org/

Open msys terminal:

    pacman -S mingw-w64-ucrt-x86_64-gcc

    pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_image

To get all the needed dlls:

    ldd app.exe | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" bin

All needed dlls will be bundled in the bin directory.

**MacOS**:

Install brew

https://brew.sh/

    brew install sdl2 sdl2_image sdl2_ttf