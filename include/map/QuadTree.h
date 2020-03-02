//
// Created by adrien on 17/01/20.
//

#ifndef INC_71K2LEDEB_QUADTREE_H
#define INC_71K2LEDEB_QUADTREE_H

#include "map/Chunk.h"
#include "out/WriteObj.h"
#include <map>

class QuadTreeNode
{
public:
    unsigned int _size;
    std::vector<std::vector<float>>	_map;
    Chunk   _chunk;
    glm::vec2   _pos;
public:
    std::shared_ptr<QuadTreeNode> _north = nullptr;
    std::shared_ptr<QuadTreeNode> _east = nullptr;
    std::shared_ptr<QuadTreeNode> _south = nullptr;
    std::shared_ptr<QuadTreeNode> _west = nullptr;

    std::shared_ptr<QuadTreeNode> _next = nullptr;

    std::shared_ptr<QuadTreeNode> _northEast = nullptr;
    std::shared_ptr<QuadTreeNode> _northWest = nullptr;
    std::shared_ptr<QuadTreeNode> _southEast = nullptr;
    std::shared_ptr<QuadTreeNode> _southWest = nullptr;
public:
    QuadTreeNode(unsigned int size, const glm::vec2 &,
                 const std::shared_ptr<QuadTreeNode> &,
                 const std::shared_ptr<QuadTreeNode> &,
                 const std::shared_ptr<QuadTreeNode> &,
                 const std::shared_ptr<QuadTreeNode> &);
};

class QuadTree
{
public:
    std::map<int, int>              _pos;
    glm::ivec2                      _currentPos;
    unsigned int                    _power;
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;
private:
    std::shared_ptr<QuadTreeNode>           _current;
public:
    QuadTree(unsigned int);
    void    gatherChunks();
    void    addEastChunk();
};

#endif //INC_71K2LEDEB_QUADTREE_H
