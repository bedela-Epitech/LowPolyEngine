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

QuadTreeNode::QuadTreeNode(unsigned int size, const glm::vec2 &pos,
                           const Matrix<float> &northMap,
                           const Matrix<float> &eastMap,
                           const Matrix<float> &southMap,
                           const Matrix<float> &westMap)
                           : _pos(pos)
{
    Chunk chunk(size);
    _map = chunk.generateMap(glm::vec2(_pos.x * (size - 1), _pos.y * (size - 1)), northMap, eastMap, southMap, westMap);
    _activationMap = chunk.mapSimplify(_map);
}

/////////////////////
//
//      QUAD TREE
//
/////////////////////

QuadTree::QuadTree(unsigned int size) : _size(size)
{
    _currentPos = {0, 0};
    std::cout << "size = " << _size << std::endl;
    Matrix<float> noMap;
    auto ptr = std::make_shared<QuadTreeNode>(_size, glm::vec2(0, 0), noMap, noMap, noMap, noMap);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);
}

glm::vec3   getColor(float height, float yNormal)
{
    glm::vec3 grey(0.28f, 0.28f, 0.28f);
    glm::vec3 green(.40, .45, .1);
    glm::vec3 darkGreen(.18f, .32f, .14f);
    glm::vec3 mount(.4, .3, .1);
    glm::vec3 color = green;
    mount = darkGreen;
    glm::vec3 white(.5f, .5f, .5f);
    if (height > -50.f)
    {
        color = darkGreen * ((height + 50.f) / 50.f) +
                green * (-height / 50.f);
    }

    if (height > 0.f)
    {
        color = mount;
        if (height < 50.f)
            color = darkGreen * ((50.f - height) / 50.f) +
                    mount * (height / 50.f);


    }
    if (height > 50.f)
    {
        float ratio = (yNormal - 0.9f) * 10.f;
        color -= (color * .3f);
        color += (((green * ratio) + darkGreen * (1.f - ratio)) / 4.f);
        if (yNormal < 0.9f)
            color = darkGreen - (darkGreen * 0.1f);
    }

    return  color;
}

void QuadTree::gatherChunks()
{
    _vertices.clear();
    _colors.clear();
    _normals.clear();
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
                if (quad->_activationMap[i][j])
                {
                    maxHeight = std::max(map.at(i, j), maxHeight);
                    minHeight = std::min(map.at(i, j), minHeight);
                    coords.push_back(i + (xMap * (int)_size));
                    coords.push_back(j + (zMap * (int)_size));
                }
            }
        }
    }
    float range = maxHeight - minHeight;
    if (coords.empty()) {
        std::cout << "Warning : no map" << std::endl;
        return;
    }
    delaunator::Delaunator d(coords);
    Perlin p;
    float ultraMax = -1000;
    float ultraMin = 1000;
    for(std::size_t i = 0; i < d.triangles.size(); i += 3)
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
            // know in which chunk we are
            int xFind = x[j] / (int)_size;
            int zFind = z[j] / (int)_size;
            // if a chunk is size 10 and the xPosition is 5 :
            // 5 / 10 = 0, chunk X position is 0
            // but -5 /10 = 0, which is false, we are actually
            // in the chunk X position -1. So we decrement to patch this
            xFind -= (x[j] < 0);
            zFind -= (z[j] < 0);
            // get the chunk with the help of its position
            auto [pos, quad] = *_miniMap.find({xFind, zFind});
            auto [xPos, zPos] = pos;
            // shift the absolute position to the map position
            xPos  = x[j] - (int)_size * xPos;
            zPos = z[j] - (int)_size * zPos;
            h[j] = (quad->_map.at(xPos, zPos) + p.getHeight(x[j], z[j]));
        }
        ultraMax = std::max(ultraMax, h[1]);
        ultraMin = std::min(ultraMin, h[1]);
        glm::vec3 v0(x[1] * 8.f, h[1], z[1] * 8.f);
        glm::vec3 v1(x[2] * 8.f, h[2], z[2] * 8.f);
        glm::vec3 v2(x[0] * 8.f, h[0], z[0] * 8.f);
        glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        _vertices.push_back(v0);
        _vertices.push_back(v1);
        _vertices.push_back(v2);
        _colors.emplace_back(getColor((h[0] + h[1] + h[2]) / 3.f, normal.y));
        _colors.emplace_back(getColor((h[0] + h[1] + h[2]) / 3.f, normal.y));
        _colors.emplace_back(getColor((h[0] + h[1] + h[2]) / 3.f, normal.y));
        _normals.push_back(normal);
    }
    std::cout << ultraMax << " " << ultraMin << std::endl;

}

void    QuadTree::addChunk(const glm::ivec2 &pos)
{
    _currentPos = pos;

    Matrix<float> northMap;
    Matrix<float> eastMap;
    Matrix<float> southMap;
    Matrix<float> westMap;

    if (auto it = _miniMap.find({_currentPos.x, _currentPos.y + 1}); it != _miniMap.end())
        northMap = it->second->_map;
    if (auto it = _miniMap.find({_currentPos.x + 1, _currentPos.y}); it != _miniMap.end())
        eastMap = it->second->_map;
    if (auto it = _miniMap.find({_currentPos.x, _currentPos.y - 1}); it != _miniMap.end())
        southMap = it->second->_map;
    if (auto it = _miniMap.find({_currentPos.x - 1, _currentPos.y}); it != _miniMap.end())
        westMap = it->second->_map;

    auto ptr = std::make_shared<QuadTreeNode>(_size, _currentPos, northMap, eastMap, southMap, westMap);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);
}