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
    Perlin p(pos, _power);
    _chunkRelief = p._noiseMap;
    Diamond diams(1.55f, _power, p._noiseMap, northMap, eastMap, southMap, westMap);
    diams.fillMap();
    updateVertices(pos * 5.f, 5, 250, diams._map);
    return diams._map;
}

glm::vec3   Chunk::getColor(float height)
{
    return (glm::vec3(1, .8, .5) * (height / 2.f) +  glm::vec3(.3, 1, .3) * ((1 - height) / 2.f));
}

void	Chunk::updateVertices(const glm::vec2 &pos, float scale, float smooth, std::vector<std::vector<float>> map)
{
    int nbIgnore = 1;
    float inc = 0.5f / static_cast<float>(map.size() * map.size());
    float color = 0.f;
    float maxHeight = 0;
    float minHeight = 0;
    float range;

    for (int x = 0; x < _chunkRelief.size(); x++)
    {
        for (int z = 0; z < _chunkRelief.size(); z++)
        {
            map[x][z] += _chunkRelief[x][z];
        }
    }
    for (const auto &line : map)
    {
        for (const auto &data : line)
        {
            maxHeight = std::max(maxHeight, data);
            minHeight = std::min(minHeight, data);
        }
    }
    range = maxHeight - minHeight;
    for (int x = 0; x < map.size() - nbIgnore; x += nbIgnore)
    {
        for (int z = 0; z < map.size() - nbIgnore; z += nbIgnore)
        {

            glm::vec3 v0(pos.x + x * scale, map[x][z + nbIgnore] * smooth - 100, pos.y + (z + nbIgnore) * scale);
            glm::vec3 v1(pos.x + (x + nbIgnore) * scale, map[x + nbIgnore][z] * smooth - 100, pos.y + z * scale);
            glm::vec3 v2(pos.x + x * scale, map[x][z] * smooth - 100, pos.y + z * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x][z]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x][z]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x][z]) / 3.f) - minHeight) / range));
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));



            v0 = glm::vec3(pos.x + (x + nbIgnore) * scale, map[x + nbIgnore][z + nbIgnore] * smooth - 100, pos.y + (z + nbIgnore) * scale);
            v1 = glm::vec3(pos.x + (x + nbIgnore) * scale, map[x + nbIgnore][z] * smooth - 100, pos.y + z * scale);
            v2 = glm::vec3(pos.x + x * scale, map[x][z + nbIgnore] * smooth - 100, pos.y + (z + nbIgnore) * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x + nbIgnore][z + nbIgnore]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x + nbIgnore][z + nbIgnore]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x + nbIgnore][z + nbIgnore]) / 3.f) - minHeight) / range));
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));

            color += inc;
        }
    }
}