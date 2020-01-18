//
// Created by adrien on 17/01/20.
//

#include "map/QuadTree.h"

QuadTreeNode::QuadTreeNode(unsigned int power) : _chunk(power)
{
    _size = (unsigned int)pow(2, power) + 1;
    _map = std::vector<std::vector<float>>(_size, std::vector<float>(_size, 0.0));

    std::vector<std::vector<float>> northMap;
    std::vector<std::vector<float>> eastMap;
    std::vector<std::vector<float>> southMap;
    std::vector<std::vector<float>> westMap;

    if (_north != nullptr)
        northMap = _north->_map;
    if (_east != nullptr)
        eastMap = _east->_map;
    if (_south != nullptr)
        southMap = _south->_map;
    if (_west != nullptr)
        westMap = _west->_map;

    _chunk.generateMap(northMap, eastMap, southMap, westMap);
}

QuadTree::QuadTree(unsigned int power)
{
    _power = power;
    _center = std::make_shared<QuadTreeNode>(_power);
}

void QuadTree::gatherChunks()
{
    auto chunk = _center;
    while (chunk != nullptr)
    {
        _vertices.insert(_vertices.end(), chunk->_chunk._vertices.begin(), chunk->_chunk._vertices.end());
        _normals.insert(_normals.end(), chunk->_chunk._normals.begin(), chunk->_chunk._normals.end());
        _colors.insert(_colors.end(), chunk->_chunk._colors.begin(), chunk->_chunk._colors.end());
        chunk = chunk->_east;
    }
}

void    QuadTree::addEastChunk()
{
   _center->_east = std::make_shared<QuadTreeNode>(_power);
   _center->_east->_west = _center;
}
