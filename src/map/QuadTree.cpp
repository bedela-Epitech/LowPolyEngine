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
    _currentPos = {0, 0};
    _power = power;
    _pos.push_back(_currentPos);
    _current = std::make_shared<QuadTreeNode>(_power, glm::vec2(0, 0), nullptr, nullptr, nullptr, nullptr);
    _current->_next = _current;
}

void QuadTree::gatherChunks()
{
    auto quad = _current;
    float maxHeight = std::numeric_limits<float>::lowest();
    float minHeight = std::numeric_limits<float>::max();
    for (const auto pos : _pos)
    {
        for (const auto &line : quad->_map)
        {
            for (const auto &height : line)
            {
                maxHeight = std::max(height, maxHeight);
                minHeight = std::min(height, minHeight);
            }
        }
        quad = quad->_next;
    }
    for (const auto pos : _pos)
    {
        quad->_chunk.updateVertices(5, 250, quad->_map, maxHeight, minHeight);
        _vertices.insert(_vertices.end(), quad->_chunk._vertices.begin(), quad->_chunk._vertices.end());
        _normals.insert(_normals.end(), quad->_chunk._normals.begin(), quad->_chunk._normals.end());
        _colors.insert(_colors.end(), quad->_chunk._colors.begin(), quad->_chunk._colors.end());
        quad = quad->_next;
    }
    //WriteObj::exportToObj(_vertices, _normals);
}

void    QuadTree::addEastChunk()
{
    _currentPos.x++;
    _pos.push_back(_currentPos);
   _current->_east = std::make_shared<QuadTreeNode>(_power, _currentPos, nullptr, nullptr, nullptr, _current);
   _current->_east->_next = _current->_next;
   _current->_next = _current->_east;
   // smooth transition
   /*float height;
   auto size = _current->_map.size();
   for (int i = 0; i < size; i++)
   {
       height = (_current->_map[size - 2][i] + _current->_east->_map[1][i]) / 2.f + ((rand() % 10) / 750.f) - (5.f / 750.f);
       _current->_map[size - 1][i] = height;
       _current->_east->_map[0][i] = height;
   }*/
   _current = _current->_next;
}

void    QuadTree::addWestChunk()
{
    _currentPos.x--;
    _pos.push_back(_currentPos);
    _current->_west = std::make_shared<QuadTreeNode>(_power, _currentPos, nullptr, _current, nullptr, nullptr);
    _current->_west->_next = _current->_next;
    _current->_next = _current->_west;
    _current = _current->_next;
}

void    QuadTree::addNorthChunk()
{
    _currentPos.y++;
    _pos.push_back(_currentPos);
    _current->_north = std::make_shared<QuadTreeNode>(_power, _currentPos, nullptr, nullptr, _current, nullptr);
    _current->_north->_next = _current->_next;
    _current->_next = _current->_north;
    _current = _current->_next;
}

void    QuadTree::addSouthChunk()
{
    _currentPos.y--;
    _pos.push_back(_currentPos);
    _current->_south = std::make_shared<QuadTreeNode>(_power, _currentPos, _current, nullptr, nullptr, nullptr);
    _current->_south->_next = _current->_next;
    _current->_next = _current->_south;
    _current = _current->_next;
}