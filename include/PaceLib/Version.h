#pragma once

#include <string>


#define PACELIB_MAJOR_VERSION   0
#define PACELIB_MINOR_VERSION   4
#define PACELIB_PATCHLEVEL      1

namespace PaceLib
{
    std::string GetVersion();

    unsigned int GetVersionMajor();
    unsigned int GetVersionMinor();
    unsigned int GetVersionPatch();
}
