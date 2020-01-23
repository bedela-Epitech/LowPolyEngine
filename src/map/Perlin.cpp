//
// Created by adrien on 13/12/19.
//

#include "map/Perlin.h"

Perlin::Perlin(const glm::vec2 &pos, int power)
{
    PerlinNoise noise;

    const uint32_t width = pow(2, power) + 1, height = pow(2, power) + 1;
    float  *noiseMapPtr = new float[width * height];
    std::vector<float> lineMap;


    uint32_t numLayers = 5;
    float maxVal = 0;
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            float fractal = 0;
            float amplitude = 1;
            glm::vec3 pt = glm::vec3(i + pos.y, 0, j + pos.x) * (1 / 128.f);
            for (uint32_t k = 0; k < numLayers; ++k) {
                fractal += (1 + noise.eval(pt)) * 0.5 * amplitude;
                pt *= 2;
                amplitude *= 0.5;
            }
            if (fractal > maxVal) maxVal = fractal;
            noiseMapPtr[j * width + i] = fractal;
        }
    }

    for (uint32_t i = 0; i < width * height; ++i)
        noiseMapPtr[i] /= maxVal;

    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            lineMap.push_back(noiseMapPtr[j * width + i]);
        }
        _noiseMap.push_back(lineMap);
        lineMap.clear();
    }
}
