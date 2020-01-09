//
// Created by adrien on 03/01/20.
//

#include "map/Chunk.h"

Chunk::Chunk(int power)
{
    Perlin p(power);
    _chunkRelief = p._noiseMap;
    Diamond diams(3.55f, power, p._noiseMap);
    diams.fillMap();
    updateVertices(5, 250, diams._map);
}

void	Chunk::updateVertices(float scale, float smooth, std::vector<std::vector<float>> &map)
{
    int nbIgnore = 5;
    float inc = 0.5f / static_cast<float>(map.size() * map.size());
    float color = 0.f;
    float maxHeight = 0;
    float minHeight = 0;
    for (const auto &line : map)
    {
        for (const auto &data : line)
        {
            maxHeight = std::max(maxHeight, data);
            minHeight = std::min(minHeight, data);
        }
    }
    for (int x = 0; x < _chunkRelief.size(); x++)
    {
        for (int z = 0; z < _chunkRelief.size(); z++)
        {
            map[x][z] += _chunkRelief[x][z];
        }
    }
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
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));



            v0 = glm::vec3((x + nbIgnore) * scale, map[x + nbIgnore][z + nbIgnore] * smooth - 100, (z + nbIgnore) * scale);
            v1 = glm::vec3((x + nbIgnore) * scale, map[x + nbIgnore][z] * smooth - 100, z * scale);
            v2 = glm::vec3(x * scale, map[x][z + nbIgnore] * smooth - 100, (z + nbIgnore) * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));

            color += inc;
        }
    }
}