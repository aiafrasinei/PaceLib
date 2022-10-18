#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "../externals/nlohmann/json.hpp"


using json = nlohmann::json;

class Configuration
{
public:
    Configuration(std::string fname);
    ~Configuration();

    auto Get(std::string name)
    {
        return j[name];
    }

    void Reload();

    void Set(std::string key, std::string val);

    void Set(std::string key, int val);

    void Set(std::string key, bool val);

    void Set(std::string key, json j);

    void Dump();
private:
    std::ifstream ifs;
    std::string jsons;
    json j;
    std::string fname;
};
