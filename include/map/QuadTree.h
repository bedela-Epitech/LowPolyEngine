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
    QuadTreeNode(unsigned int size, const glm::vec2 &,
                 std::shared_ptr<QuadTreeNode> ,
                 std::shared_ptr<QuadTreeNode> ,
                 std::shared_ptr<QuadTreeNode> ,
                 std::shared_ptr<QuadTreeNode> );
};

class QuadTree
{
public:
    std::map<std::pair<int, int>, std::shared_ptr<QuadTreeNode>> _miniMap;
    glm::ivec2                      _currentPos;
    unsigned int                    _power;
    unsigned int                    _size;
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;

public:
    QuadTree(unsigned int);
    void    gatherChunks();
    void    addChunk(const glm::ivec2 &);
    void    mergeChunks(std::shared_ptr<QuadTreeNode>,
                        std::shared_ptr<QuadTreeNode>,
                        std::shared_ptr<QuadTreeNode>,
                        std::shared_ptr<QuadTreeNode>,
                        std::shared_ptr<QuadTreeNode>);
};

#endif //INC_71K2LEDEB_QUADTREE_H
