//
// Created by adrien on 17/01/20.
//

#include "map/QuadTree.h"
#include <cmath>
/////////////////////
//
//      QUAD TREE NODE
//
/////////////////////

QuadTreeNode::QuadTreeNode(unsigned int power, const glm::vec2 &pos,
                           const std::vector<std::vector<float>> &northMap,
                           const std::vector<std::vector<float>> &eastMap,
                           const std::vector<std::vector<float>> &southMap,
                           const std::vector<std::vector<float>> &westMap) :
        _chunk(power), _pos(pos)
{
    _size = (unsigned int)pow(2, power) + 1;
    _map = _chunk.generateMap(glm::vec2(_pos.x * (_size - 1), _pos.y * (_size - 1)), northMap, eastMap, southMap, westMap);
    _activationMap = _chunk._activationMap;
}

/////////////////////
//
//      QUAD TREE
//
/////////////////////

QuadTree::QuadTree(unsigned int power)
{
    _currentPos = {0, 0};
    _power = power;

    std::vector<std::vector<float>> noMap;
    auto ptr = std::make_shared<QuadTreeNode>(_power, glm::vec2(0, 0), noMap, noMap, noMap, noMap);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);
    _size = ptr->_size;
}

glm::vec3   getColor(float height)
{
    return ((glm::vec3(.4, .3, .1) * (height / 1.5f) +  glm::vec3(.3, .4, .2) * ((1.f - height))) * 1.5f);
}

void QuadTree::gatherChunks()
{
    float maxHeight = std::numeric_limits<float>::lowest();
    float minHeight = std::numeric_limits<float>::max();
    std::vector<double> coords;
    for (const auto &[pos, quad] : _miniMap)
    {
        auto [xMap, zMap] = pos;
        auto map = quad->_map;
        for (int i = 1; i < _size - 1; ++i)
        {
            for (int j = 1; j < _size - 1; ++j)
            {
                if (quad->_activationMap[i][j]/* && xMap >= 0 && zMap >= 0*/)
                {
                    maxHeight = std::max(map[i][j] * 250.f - 100, maxHeight);
                    minHeight = std::min(map[i][j] * 250.f - 100, minHeight);
                    coords.push_back(i + (xMap * (int)_size));
                    coords.push_back(j + (zMap * (int)_size));
                }
            }
        }
    }
    std::cout << "before range" << std::endl;
    float range = maxHeight - minHeight;
    std::cout << "after range" << std::endl;
    delaunator::Delaunator d(coords);
    std::cout << "after range" << std::endl;
    for(std::size_t i = 0; i < d.triangles.size(); i+=3)
    {
        int x[3];
        int z[3];
        float h[3];
        x[0] = d.coords[2 * d.triangles[i]];
        z[0] = d.coords[2 * d.triangles[i] + 1];
        x[1] = d.coords[2 * d.triangles[i + 1]];
        z[1] = d.coords[2 * d.triangles[i + 1] + 1];
        x[2] = d.coords[2 * d.triangles[i + 2]];
        z[2] = d.coords[2 * d.triangles[i + 2] + 1];
        for (int j = 0; j < 3; ++j)
        {
            int xFind = x[j] / (int)_size;
            int zFind = z[j] / (int)_size;
            if (x[j] < 0)
                xFind--;
            if (z[j] < 0)
                zFind--;

            auto [pos, map] = *_miniMap.find({xFind, zFind});
            auto [xPos, zPos] = pos;
            h[j] = map->_map[x[j] - (int)_size * xPos][z[j] - (int)_size * zPos] * 250.f - 100.f;
        }

        glm::vec3 v0(x[1] * 5.0, h[1], z[1] * 5.0);
        glm::vec3 v1(x[2] * 5.0, h[2], z[2] * 5.0);
        glm::vec3 v2(x[0] * 5.0, h[0], z[0] * 5.0);

        _vertices.push_back(v0);
        _vertices.push_back(v1);
        _vertices.push_back(v2);
        _colors.emplace_back(getColor((((h[0], h[1], h[2]) / 3.f) - minHeight) / range));
        _colors.emplace_back(getColor((((h[0], h[1], h[2]) / 3.f) - minHeight) / range));
        _colors.emplace_back(getColor((((h[0], h[1], h[2]) / 3.f) - minHeight) / range));
        _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));

        /*glm::vec3 v0(i * 5, 0, i * 5);
        glm::vec3 v1((i + 1) * 5, 0, i * 5);
        glm::vec3 v2(i * 5, 0, (i + 1) * 5);

        _vertices.push_back(v0);
        _vertices.push_back(v1);
        _vertices.push_back(v2);

        _colors.emplace_back(glm::vec3(1, 0, 0));
        _colors.emplace_back(glm::vec3(1, 0, 0));
        _colors.emplace_back(glm::vec3(1, 0, 0));

        _normals.emplace_back(glm::vec3(1, 0, 0));*/
    }

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
    //WriteObj::exportToObj(_vertices, _normals);
}

void    QuadTree::addChunk(const glm::ivec2 &adder)
{
    _currentPos += adder;

    std::vector<std::vector<float>> northMap;
    std::vector<std::vector<float>> eastMap;
    std::vector<std::vector<float>> southMap;
    std::vector<std::vector<float>> westMap;

    if (auto it = _miniMap.find({_currentPos.x, _currentPos.y + 1}); it != _miniMap.end())
        northMap = it->second->_map;
    if (auto it = _miniMap.find({_currentPos.x + 1, _currentPos.y}); it != _miniMap.end())
        eastMap = it->second->_map;
    if (auto it = _miniMap.find({_currentPos.x, _currentPos.y - 1}); it != _miniMap.end())
        southMap = it->second->_map;
    if (auto it = _miniMap.find({_currentPos.x - 1, _currentPos.y}); it != _miniMap.end())
        westMap = it->second->_map;

    auto ptr = std::make_shared<QuadTreeNode>(_power, _currentPos, northMap, eastMap, southMap, westMap);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);
}