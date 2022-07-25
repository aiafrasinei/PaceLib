#pragma once

#include <string>


namespace PaceLib
{
    std::string GetVersion();

    unsigned int GetVersionMajor();
    unsigned int GetVersionMinor();
    unsigned int GetVersionPatch();
}
