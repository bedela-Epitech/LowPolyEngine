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
                           const std::vector<std::vector<float>> &northMap,
                           const std::vector<std::vector<float>> &eastMap,
                           const std::vector<std::vector<float>> &southMap,
                           const std::vector<std::vector<float>> &westMap) :
        _chunk(power), _pos(pos)
{
    _size = (unsigned int)pow(2, power) + 1;
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

    std::vector<std::vector<float>> noMap;
    auto ptr = std::make_shared<QuadTreeNode>(_power, glm::vec2(0, 0), noMap, noMap, noMap, noMap);
    _miniMap.emplace(std::make_pair(_currentPos.x, _currentPos.y), ptr);
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