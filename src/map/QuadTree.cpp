//
// Created by adrien on 17/01/20.
//

#include "map/QuadTree.h"

/////////////////////
//
//      QUAD TREE NODE
//
/////////////////////

QuadTreeNode::QuadTreeNode(unsigned int power, const glm::vec2 &pos,
                           std::shared_ptr<QuadTreeNode> north,
                           std::shared_ptr<QuadTreeNode> east,
                           std::shared_ptr<QuadTreeNode> south,
                           std::shared_ptr<QuadTreeNode> west) :
        _chunk(power), _pos(pos)
{
    _size = (unsigned int)pow(2, power) + 1;

    std::vector<std::vector<float>> northMap;
    std::vector<std::vector<float>> eastMap;
    std::vector<std::vector<float>> southMap;
    std::vector<std::vector<float>> westMap;

    if (north != nullptr)
        northMap = north->_map;
    if (east != nullptr)
        eastMap = east->_map;
    if (south != nullptr)
        southMap = south->_map;
    if (west != nullptr)
        westMap = west->_map;

    _map = _chunk.generateMap(glm::vec2(_pos.x * (_size - 1), _pos.y * (_size - 1)), northMap, eastMap, southMap, westMap);
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

    auto ptr = std::make_shared<QuadTreeNode>(_power, glm::vec2(0, 0), nullptr, nullptr, nullptr, nullptr);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);

    _size = ptr->_map.size();
}

void QuadTree::gatherChunks()
{
    float maxHeight = std::numeric_limits<float>::lowest();
    float minHeight = std::numeric_limits<float>::max();
    for (const auto &[pos, quad] : _miniMap)
    {
        for (const auto &line : quad->_map)
        {
            for (const auto &height : line)
            {
                maxHeight = std::max(height, maxHeight);
                minHeight = std::min(height, minHeight);
            }
        }
    }
    for (const auto &[pos, quad] : _miniMap)
    {
        quad->_chunk.updateVertices(5, 250, quad->_map, maxHeight, minHeight);
        _vertices.insert(_vertices.end(), quad->_chunk._vertices.begin(), quad->_chunk._vertices.end());
        _normals.insert(_normals.end(), quad->_chunk._normals.begin(), quad->_chunk._normals.end());
        _colors.insert(_colors.end(), quad->_chunk._colors.begin(), quad->_chunk._colors.end());
    }
    //WriteObj::exportToObj(_vertices, _normals);
}

void    QuadTree::addChunk(const glm::ivec2 &adder)
{
    _currentPos += adder;

    std::shared_ptr<QuadTreeNode> north = nullptr;
    std::shared_ptr<QuadTreeNode> east = nullptr;
    std::shared_ptr<QuadTreeNode> south = nullptr;
    std::shared_ptr<QuadTreeNode> west = nullptr;

    if (auto it = _miniMap.find({_currentPos.x, _currentPos.y + 1}); it != _miniMap.end())
        north = it->second;
    if (auto it = _miniMap.find({_currentPos.x + 1, _currentPos.y}); it != _miniMap.end())
        east = it->second;
    if (auto it = _miniMap.find({_currentPos.x, _currentPos.y - 1}); it != _miniMap.end())
        south = it->second;
    if (auto it = _miniMap.find({_currentPos.x - 1, _currentPos.y}); it != _miniMap.end())
        west = it->second;

    auto ptr = std::make_shared<QuadTreeNode>(_power, _currentPos, north, east, south, west);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);

    mergeChunks(ptr, east, north, south, west);
}


// rude merge between chunks, might need a change
void QuadTree::mergeChunks(std::shared_ptr<QuadTreeNode> ptr, std::shared_ptr<QuadTreeNode> east,
                           std::shared_ptr<QuadTreeNode> north, std::shared_ptr<QuadTreeNode> south,
                           std::shared_ptr<QuadTreeNode> west)
{

    float height;
    if (east != nullptr)
    {
        for (int i = 1; i < _size - 1; i++)
        {
            height = (ptr->_map[_size - 2][i] + east->_map[1][i]) / 2.f + ((rand() % 10) / 750.f) - (5.f / 750.f);
            ptr->_map[_size - 1][i] = height;
            east->_map[0][i] = height;
        }
    }
    if (north != nullptr)
    {
        for (int i = 1; i < _size - 1; i++)
        {
            height = (ptr->_map[i][_size - 2] + north->_map[i][1]) / 2.f + ((rand() % 10) / 750.f) - (5.f / 750.f);
            ptr->_map[i][_size - 1] = height;
            north->_map[i][0] = height;
        }
    }
    if (south != nullptr)
    {
        for (int i = 1; i < _size - 1; i++)
        {
            height = (ptr->_map[i][1] + south->_map[i][_size - 2]) / 2.f + ((rand() % 10) / 750.f) - (5.f / 750.f);
            ptr->_map[i][0] = height;
            south->_map[i][_size - 1] = height;
        }
    }
    if (west != nullptr)
    {
        for (int i = 1; i < _size - 1; i++)
        {
            height = (ptr->_map[1][i] + west->_map[_size - 2][i]) / 2.f + ((rand() % 10) / 750.f) - (5.f / 750.f);
            ptr->_map[0][i] = height;
            west->_map[_size - 1][i] = height;
        }
    }
}