//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_CHUNK_H
#define INC_71K2LEDEB_CHUNK_H


#include "delaunator.hpp"
#include "map/Perlin.h"
#include "map/Diamond.hpp"

class Chunk
{
public:
    glm::vec2 _pos;
    unsigned int _power;
    std::vector<std::vector<float>>         _chunkRelief;
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;

    std::vector<std::vector<bool>>          _activationMap;

    float                   _diagLength;
    float                   _sideLength;
public:
    Chunk(unsigned int);
    glm::vec3   getColor(float);
    std::vector<std::vector<float>>    generateMap(const glm::vec2 &, const std::vector<std::vector<float>> &, const std::vector<std::vector<float>> &,
                        const std::vector<std::vector<float>> &, const std::vector<std::vector<float>> &);
    void	updateVertices(float , float, std::vector<std::vector<float>> &, float, float);
    void    mapSimplify(const std::vector<std::vector<float>> &);
    float   calculateFlat(float, float, float, float);
    float   calculatePyramid(float, float, float, float, float);

};

#endif //INC_71K2LEDEB_CHUNK_H
