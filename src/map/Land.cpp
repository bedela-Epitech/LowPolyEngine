//
// Created by adrien on 09/01/20.
//

#include "map/Land.h"

Land::Land()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    _gen = std::mt19937(rd());
    _height = 0.1f;
}

float   Land::boundedRand(float min, float max)
{
    std::uniform_real_distribution<> dis(min, max);
    return (static_cast<float>(dis(_gen)));
}
