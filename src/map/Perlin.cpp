//
// Created by adrien on 13/12/19.
//

#include "map/Perlin.h"
Perlin::Perlin()
{ }

float Perlin::getHeight(int x, int y)
{
    uint32_t numLayers = 5;
    float fractal = 0;
    float amplitude = 0.1;
    glm::vec3 pt = glm::vec3(x, 0, y) * (1 / 128.f);

    for (uint32_t k = 0; k < numLayers; ++k) {
        fractal += (1.f + _noise.eval(pt)) * 0.5f * amplitude;
        pt *= 2;
        amplitude *= 0.5;
    }
    return (fractal);
}

