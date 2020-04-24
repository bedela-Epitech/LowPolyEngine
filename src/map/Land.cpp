//
// Created by adrien on 09/01/20.
//

#include "map/Land.h"

Land::Land()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    _gen = std::mt19937(rd());
    _height = 12.5f;
}

float   Land::boundedRand()
{
    std::uniform_real_distribution<> dis(-_height, _height);
    return (static_cast<float>(dis(_gen)));
}
