//
// Created by adrien on 03/01/20.
//

#include "map/Chunk.h"

Chunk::Chunk(int power)
{
    Perlin p(power);
    _chunkRelief = p._noiseMap;
    Diamond diams(1.55f, power, p._noiseMap);
    diams.fillMap();
    updateVertices(5, 250, diams._map);
}

glm::vec3   Chunk::getColor(float height)
{
    return (glm::vec3(1, .8, .5) * (height / 2.f) +  glm::vec3(.3, 1, .3) * ((1 - height) / 2.f));
}

void	Chunk::updateVertices(float scale, float smooth, std::vector<std::vector<float>> &map)
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
    for (int x = 0; x < _chunkRelief.size() - nbIgnore; x += nbIgnore)
    {
        for (int z = 0; z < _chunkRelief.size() - nbIgnore; z += nbIgnore)
        {

            glm::vec3 v0(x * scale, map[x][z + nbIgnore] * smooth - 100, (z + nbIgnore) * scale);
            glm::vec3 v1((x + nbIgnore) * scale, map[x + nbIgnore][z] * smooth - 100, z * scale);
            glm::vec3 v2(x * scale, map[x][z] * smooth - 100, z * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x][z]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x][z]) / 3.f) - minHeight) / range));
            _colors.emplace_back(getColor((((map[x][z + nbIgnore] + map[x + nbIgnore][z] + map[x][z]) / 3.f) - minHeight) / range));
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));



            v0 = glm::vec3((x + nbIgnore) * scale, map[x + nbIgnore][z + nbIgnore] * smooth - 100, (z + nbIgnore) * scale);
            v1 = glm::vec3((x + nbIgnore) * scale, map[x + nbIgnore][z] * smooth - 100, z * scale);
            v2 = glm::vec3(x * scale, map[x][z + nbIgnore] * smooth - 100, (z + nbIgnore) * scale);
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