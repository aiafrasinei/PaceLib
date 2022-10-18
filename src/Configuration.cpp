#include "Configuration.hpp"
#include <map>
#include <stdlib.h>


using json = nlohmann::json;

Configuration::Configuration(std::string fname)
{
    this->fname = fname;

    ifs.open(fname);
    jsons.assign(std::istreambuf_iterator<char>(ifs) , std::istreambuf_iterator<char>());

    j = json::parse(jsons);
    ifs.close();
}

Configuration::~Configuration()
{

}

void Configuration::Reload()
{
    ifs.open(fname);
    jsons.assign(std::istreambuf_iterator<char>(ifs) , std::istreambuf_iterator<char>());
    j = json::parse(jsons);
    ifs.close();
}

void Configuration::Set(std::string key, std::string val) {
    j[key] = val;
}

void Configuration::Set(std::string key, int val) {
    j[key] = val;
}

void Configuration::Set(std::string key, bool val) {
    j[key] = val;
}

void Configuration::Set(std::string key, json j) {
    j[key] = j;
}

void Configuration::Dump() {
    std::ofstream ofs(fname, std::ofstream::out);
    ofs << j.dump();
    ofs.close();
    Reload();
}

