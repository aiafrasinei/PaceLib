#pragma once

#include <random>

class Random
{

public:
    Random() {
    }

    ~Random() {
    }

    int Get(int first, int second)
    {
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(first, second);
        return distr(gen);
    }

    float Get(float first, float second)
    {
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distr(first, second);
        return distr(gen);
    }

private:
    std::random_device rd;
};