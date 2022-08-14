#include "Version.h"

static unsigned int major = 0;
static unsigned int minor = 1;
static unsigned int patch = 3;

std::string GetVersion()
{
    return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

unsigned int GetVersionMajor()
{
    return major;
}

unsigned int GetVersionMinor()
{
    return minor;
}

unsigned int GetVersionPatch()
{
    return patch;
}