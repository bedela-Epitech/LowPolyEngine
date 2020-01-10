//
// Created by adrien on 09/01/20.
//

#ifndef INC_71K2LEDEB_BIOME_H
#define INC_71K2LEDEB_BIOME_H

#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <random>


class Diamond;

class Biome
{
protected:
    std::mt19937    _gen;
    float       _height;
    glm::vec3   _color;
public:
    virtual float   boundedRand(float, float) = 0;

    friend Diamond;
};

#endif //INC_71K2LEDEB_BIOME_H
