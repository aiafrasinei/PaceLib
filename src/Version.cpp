#include "Version.h"


std::string GetVersion()
{
    return std::to_string(PACELIB_MAJOR_VERSION) + "." + std::to_string(PACELIB_MINOR_VERSION) + "." + std::to_string(PACELIB_PATCHLEVEL);
}

unsigned int GetVersionMajor()
{
    return PACELIB_MAJOR_VERSION;
}

unsigned int GetVersionMinor()
{
    return PACELIB_MINOR_VERSION;
}

unsigned int GetVersionPatch()
{
    return PACELIB_PATCHLEVEL;
}