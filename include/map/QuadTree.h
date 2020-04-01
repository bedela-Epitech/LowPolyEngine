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
    std::vector<std::vector<float>>	_map;
    std::vector<std::vector<bool>>	_activationMap;
    unsigned int                    _size;
    Chunk                           _chunk;
    glm::vec2                       _pos;

public:
    QuadTreeNode(unsigned int size, const glm::vec2 &,
                 const std::vector<std::vector<float>> & ,
                 const std::vector<std::vector<float>> & ,
                 const std::vector<std::vector<float>> & ,
                 const std::vector<std::vector<float>> & );
};

class QuadTree
{
public:
    std::map<std::pair<int, int>, std::shared_ptr<QuadTreeNode>> _miniMap;
    unsigned int                    _size;
    glm::ivec2                      _currentPos;
    unsigned int                    _power;
    std::vector<glm::vec3>          _vertices;
    std::vector<glm::vec3>          _normals;
    std::vector<glm::vec3>          _colors;

public:
    QuadTree(unsigned int);
    void    gatherChunks();
    void    addChunk(const glm::ivec2 &);
};

#endif //INC_71K2LEDEB_QUADTREE_H
