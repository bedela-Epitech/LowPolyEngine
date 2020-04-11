//
// Created by adrien on 17/01/20.
//

#ifndef INC_71K2LEDEB_QUADTREE_H
#define INC_71K2LEDEB_QUADTREE_H

#include "map/Chunk.h"
#include "out/WriteObj.h"
#include <map>
#include "encapsulation/Matrix.h"
class QuadTreeNode
{
public:
    Matrix<float>	_map;
    std::vector<std::vector<bool>>	_activationMap;
    glm::vec2                       _pos;

public:
    QuadTreeNode(unsigned int size, const glm::vec2 &,
                 const Matrix<float> &,
                 const Matrix<float> &,
                 const Matrix<float> &,
                 const Matrix<float> &);
};

class QuadTree
{
public:
    std::map<std::pair<int, int>, std::shared_ptr<QuadTreeNode>> _miniMap;
    unsigned int                    _size;
    glm::ivec2                      _currentPos;

    std::vector<glm::vec3>          _vertices;
    std::vector<glm::vec3>          _normals;
    std::vector<glm::vec3>          _colors;

public:
    explicit QuadTree(unsigned int);
    void    gatherChunks();
    void    addChunk(const glm::ivec2 &);
};

#endif //INC_71K2LEDEB_QUADTREE_H
