//
// Created by adrien on 09/01/20.
//

#include "map/Mountain.h"

Mountain::Mountain()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    _gen = std::mt19937(rd());
    _height = 3.0f;
}

float   Mountain::boundedRand(float min, float max)
{
    std::uniform_real_distribution<> dis(min / 2.f, max);
    return (static_cast<float>(dis(_gen)));
}

