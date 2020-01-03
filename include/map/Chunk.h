//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_CHUNK_H
#define INC_71K2LEDEB_CHUNK_H


#include "map/Perlin.h"
#include "map/Diamond.hpp"

class Chunk
{
public:
    std::vector<std::vector<float>>         _chunkRelief;
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;
public:
    Chunk(int);

    void	updateVertices(float , float, std::vector<std::vector<float>> &);


};

#endif //INC_71K2LEDEB_CHUNK_H
