//
// Created by adrien on 17/01/20.
//

#include "map/QuadTree.h"

QuadTreeNode::QuadTreeNode(unsigned int power, const glm::vec2 &pos,
                           const std::shared_ptr<QuadTreeNode> &north,
                           const std::shared_ptr<QuadTreeNode> &east,
                           const std::shared_ptr<QuadTreeNode> &south,
                           const std::shared_ptr<QuadTreeNode> &west) :
                           _north(north), _east(east), _south(south), _west(west), _chunk(power), _pos(pos)
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

    _map = _chunk.generateMap(glm::vec2(_pos.x * (_size - 1), _pos.y * (_size - 1)), northMap, eastMap, southMap, westMap);
}

QuadTree::QuadTree(unsigned int power)
{
    _power = power;
    _center = std::make_shared<QuadTreeNode>(_power, glm::vec2(0, 0), nullptr, nullptr, nullptr, nullptr);
}

void QuadTree::gatherChunks()
{
    auto quad = _center;
    float maxHeight = std::numeric_limits<float>::lowest();
    float minHeight = std::numeric_limits<float>::max();
    while (quad != nullptr)
    {
        for (const auto &line : quad->_map)
        {
            for (const auto &height : line)
            {
                maxHeight = std::max(height, maxHeight);
                minHeight = std::min(height, minHeight);
            }
        }
        quad = quad->_east;
    }
    quad = _center;
    while (quad != nullptr)
    {
        quad->_chunk.updateVertices(5, 250, quad->_map, maxHeight, minHeight);
        _vertices.insert(_vertices.end(), quad->_chunk._vertices.begin(), quad->_chunk._vertices.end());
        _normals.insert(_normals.end(), quad->_chunk._normals.begin(), quad->_chunk._normals.end());
        _colors.insert(_colors.end(), quad->_chunk._colors.begin(), quad->_chunk._colors.end());
        quad = quad->_east;
    }
    //WriteObj::exportToObj(_vertices, _normals);
}

void    QuadTree::addEastChunk()
{
   _center->_east = std::make_shared<QuadTreeNode>(_power, glm::vec2(1, 0), nullptr, nullptr, nullptr, _center);
}
