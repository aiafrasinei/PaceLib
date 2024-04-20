How to install

***

This is the recomended way to use PaceLib.

Can be used in other ways but your on your own there.

Prerequisites:
- c++23 compiler
- SDL3, SDL3_image, SDL3_ttf 
- cmake

**Linux**:

Install the prerequisites using you own distro install system.

fedora:

    dnf install SDL3 SDL3-devel SDL3_image SDL3_image-devel SDL3_ttf SDL3_ttf-devel

ubuntu:

    apt install libsdl libsdl3-dev libsdl3_image libsdl3_image-dev libsdl3_ttf libsdl3_ttf-dev

**Windows**:

Install msys2

https://www.msys2.org/

Open msys terminal:

    pacman -S mingw-w64-ucrt-x86_64-gcc

    pacman -S mingw-w64-x86_64-SDL3 mingw-w64-x86_64-SDL3_ttf mingw-w64-x86_64-SDL3_image

To get all the needed dlls:

    ldd app.exe | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" bin

All needed dlls will be bundled in the bin directory.

**MacOS**:

Install brew

https://brew.sh/

    brew install sdl3 sdl3_image sdl3_ttf