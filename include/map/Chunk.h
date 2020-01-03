//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_CHUNK_H
#define INC_71K2LEDEB_CHUNK_H

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

class Chunk
{
    std::vector<glm::vec3>                  _vertices;
    std::vector<glm::vec3>                  _normals;
    std::vector<glm::vec3>                  _colors;
};

#endif //INC_71K2LEDEB_CHUNK_H
