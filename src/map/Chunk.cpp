//
// Created by adrien on 03/01/20.
//

#include "map/Chunk.h"

Chunk::Chunk(unsigned int size) : _size(size)
{ }

Matrix<float>        Chunk::generateMap(const glm::vec2 &pos,
                                        const Matrix<float> &northMap, const Matrix<float> &eastMap,
                                        const Matrix<float> &southMap, const Matrix<float> &westMap)
{
    Diamond diams(_size, northMap, eastMap, southMap, westMap);
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

std::vector<std::vector<bool>> Chunk::mapSimplify(const Matrix<float> &map) const
{
    double pScore;
    double fScore;
    double ratio;
    std::vector<std::vector<bool>> activationMap;
    std::vector<bool> line = std::vector<bool>(map.rows(), true);

    activationMap.emplace_back(map.rows(), true);
    for (int i = 1; i < map.rows() - 1; ++i)
    {
        for (int j = 1; j < map.cols() - 1; ++j)
        {
            fScore = calculateFlat(map.at(i - 1, j - 1), map.at(i - 1, j), map.at(i - 1, j + 1),
                                   map.at(i, j + 1), map.at(i + 1, j + 1), map.at(i + 1, j),
                                   map.at(i + 1, j - 1), map.at(i, j - 1));
            pScore = calculatePyramid(map.at(i - 1, j - 1), map.at(i - 1, j), map.at(i - 1, j + 1),
                                      map.at(i, j + 1), map.at(i + 1, j + 1), map.at(i + 1, j),
                                      map.at(i + 1, j - 1), map.at(i, j - 1), map.at(i, j));
            ratio = fScore / pScore;
            line[j] = ratio <= _phi;
        }
        activationMap.push_back(line);
    }
    activationMap.emplace_back(map.rows(), true);
    return (activationMap);
}