//
// Created by adrien on 03/01/20.
//

#include "map/Chunk.h"

Chunk::Chunk(unsigned int power)
{
    _power = power;
}

std::vector<std::vector<float>>        Chunk::generateMap(const glm::vec2 &pos, const std::vector<std::vector<float>> &northMap, const std::vector<std::vector<float>> &eastMap,
                                                          const std::vector<std::vector<float>> &southMap, const std::vector<std::vector<float>> &westMap)
{
    _pos = pos;
    Diamond diams(0.55f, _power, northMap, eastMap, southMap, westMap);
    diams.fillMap();
    _pos *= 5.f;
    mapSimplify(diams._map);
    return diams._map;
}

float Chunk::calculateFlat(float A, float B, float C, float D)
{
    return (abs(A - B) + abs(B - C) + abs(C - D) + abs(D - A) + std::max(abs(B - D), abs(A - C)));
}

float Chunk::calculatePyramid(float A, float B, float C, float D, float H)
{
    return (abs(A - B) + abs(B - C) + abs(C - D) + abs(D - A) +
            abs(A - H) + abs(B - H) + abs(C - H) + abs(D - H));
}

void Chunk::mapSimplify(const std::vector<std::vector<float>> &map)
{
    float pScore;
    float fScore;
    float ratio;
    std::vector<bool> line = std::vector<bool>(map.size(), true);

    _activationMap.emplace_back(map.size(), true);
    for (int i = 1; i < map.size() - 1; ++i)
    {

        for (int j = 1; j < map[i].size() - 1; ++j)
        {
            fScore = calculateFlat(map[i - 1][j], map[i][j + 1], map[i + 1][j], map[i][j - 1]);
            pScore = calculatePyramid(map[i - 1][j], map[i][j + 1], map[i + 1][j], map[i][j - 1], map[i][j]);
            ratio = fScore / pScore;
            line[j] = ratio <= 0.6f;
        }
        _activationMap.push_back(line);
    }
    _activationMap.emplace_back(map.size(), true);
}