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
    Perlin p(_pos, _power);
    _chunkRelief = p._noiseMap;
    Diamond diams(0.55f, _power, p._noiseMap, northMap, eastMap, southMap, westMap);
    diams.fillMap();
    _pos *= 5.f;
    return diams._map;
}

glm::vec3   Chunk::getColor(float height)
{
    return ((glm::vec3(.4, .3, .1) * (height / 1.5f) +  glm::vec3(.3, .4, .2) * ((1 - height))) * 1.5f);
}

void	Chunk::updateVertices(float scale, float smooth, std::vector<std::vector<float>> &map, float maxHeight, float minHeight)
{
    int nbIgnore = (int)pow(2, std::max(0, (int)_power - 8));
    float range  = maxHeight - minHeight;
    std::vector<double> coords;
    for (int x = 0; x < _chunkRelief.size(); x += nbIgnore)
        for (int z = 0; z < _chunkRelief.size(); z += nbIgnore)
        {
                map[x][z] += _chunkRelief[x][z];
                coords.push_back(x);
                coords.push_back(z);
        }
    delaunator::Delaunator d(coords);

    for(std::size_t i = 0; i < d.triangles.size(); i+=3)
        {
            auto x0 = d.coords[2 * d.triangles[i]];
            auto z0 = d.coords[2 * d.triangles[i] + 1];
            auto x1 = d.coords[2 * d.triangles[i + 1]];
            auto z1 = d.coords[2 * d.triangles[i + 1] + 1];
            auto x2 = d.coords[2 * d.triangles[i + 2]];
            auto z2 = d.coords[2 * d.triangles[i + 2] + 1];

            glm::vec3 v0(_pos.x + x1 * scale, map[x1][z1] * smooth - 100, _pos.y + z1 * scale);
            glm::vec3 v1(_pos.x + x2 * scale, map[x2][z2] * smooth - 100, _pos.y + z2 * scale);
            glm::vec3 v2(_pos.x + x0 * scale, map[x0][z0] * smooth - 100, _pos.y + z0 * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(getColor((((map[x0][z0] + map[x1][z1] + map[x2][z2]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x0][z0] + map[x1][z1] + map[x2][z2]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x0][z0] + map[x1][z1] + map[x2][z2]) / 3.f) - minHeight) / range));
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));

            /*v0 = glm::vec3(_pos.x + (x + nbIgnore) * scale, map[x + nbIgnore][z + nbIgnore] * smooth - 100, _pos.y + (z + nbIgnore) * scale);
            v1 = glm::vec3(_pos.x + (x + nbIgnore) * scale, map[x + nbIgnore][z] * smooth - 100, _pos.y + z * scale);
            v2 = glm::vec3(_pos.x + x * scale, map[x][z + nbIgnore] * smooth - 100, _pos.y + (z + nbIgnore) * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x + nbIgnore][z + nbIgnore]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x + nbIgnore][z + nbIgnore]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x + nbIgnore][z + nbIgnore]) / 3.f) - minHeight) / range));
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));*/
    }
}