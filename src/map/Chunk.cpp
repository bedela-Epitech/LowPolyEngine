//
// Created by adrien on 03/01/20.
//

#include "map/Chunk.h"

Chunk::Chunk(unsigned int power) : _power(power)
{ }

std::vector<std::vector<float>>        Chunk::generateMap(const glm::vec2 &pos, const std::vector<std::vector<float>> &northMap, const std::vector<std::vector<float>> &eastMap,
                                                          const std::vector<std::vector<float>> &southMap, const std::vector<std::vector<float>> &westMap)
{
    Diamond diams(_power, northMap, eastMap, southMap, westMap);
    diams.fillMap();
    return diams._map;
}

double Chunk::calculateFlat(double A, double B, double C, double D, double E, double F, double G, double H) const
{
    return ((sqrt(1.0 + pow(A - B, 2)) * sqrt(1.0 + pow(A - H, 2))) +
            (sqrt(1.0 + pow(C - B, 2)) * sqrt(1.0 + pow(C - D, 2))) +
            (sqrt(1.0 + pow(E - D, 2)) * sqrt(1.0 + pow(E - F, 2))) +
            (sqrt(1.0 + pow(G - H, 2)) * sqrt(1.0 + pow(G - F, 2))) +
            (sqrt(2.0 + pow(D - B, 2)) * sqrt(2.0 + pow(D - F, 2))) +
            (sqrt(2.0 + pow(H - B, 2)) * sqrt(2.0 + pow(H - F, 2))));
}

double Chunk::calculatePyramid(double A, double B, double C, double D, double E, double F, double G, double H, double P) const
{
    return ((sqrt(1.0 + pow(B - P, 2)) * sqrt(1.0 + pow(B - A, 2))) +
            (sqrt(1.0 + pow(B - P, 2)) * sqrt(1.0 + pow(B - C, 2))) +
            (sqrt(1.0 + pow(D - P, 2)) * sqrt(1.0 + pow(D - C, 2))) +
            (sqrt(1.0 + pow(D - P, 2)) * sqrt(1.0 + pow(D - E, 2))) +
            (sqrt(1.0 + pow(F - P, 2)) * sqrt(1.0 + pow(F - E, 2))) +
            (sqrt(1.0 + pow(F - P, 2)) * sqrt(1.0 + pow(F - G, 2))) +
            (sqrt(1.0 + pow(H - P, 2)) * sqrt(1.0 + pow(H - G, 2))) +
            (sqrt(1.0 + pow(H - P, 2)) * sqrt(1.0 + pow(H - A, 2))));
}

std::vector<std::vector<bool>> Chunk::mapSimplify(const std::vector<std::vector<float>> &map) const
{
    double pScore;
    double fScore;
    double ratio;
    std::vector<std::vector<bool>> activationMap;
    std::vector<bool> line = std::vector<bool>(map.size(), true);

    activationMap.emplace_back(map.size(), true);
    for (int i = 1; i < map.size() - 1; ++i)
    {
        for (int j = 1; j < map[i].size() - 1; ++j)
        {
            fScore = calculateFlat(map[i - 1][j - 1], map[i - 1][j], map[i - 1][j + 1],
                                   map[i][j + 1], map[i + 1][j + 1], map[i + 1][j],
                                   map[i + 1][j - 1], map[i][j - 1]);
            pScore = calculatePyramid(map[i - 1][j - 1], map[i - 1][j], map[i - 1][j + 1],
                                      map[i][j + 1], map[i + 1][j + 1], map[i + 1][j],
                                      map[i + 1][j - 1], map[i][j - 1], map[i][j]);
            ratio = fScore / pScore;
            line[j] = ratio <= _phi;
        }
        activationMap.push_back(line);
    }
    activationMap.emplace_back(map.size(), true);
    return (activationMap);
}