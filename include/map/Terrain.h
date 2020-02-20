//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_TERRAIN_H
#define INC_71K2LEDEB_TERRAIN_H

#include "encapsulation/Shader.h"
#include "Light.hpp"
#include "map/QuadTree.h"
#include "encapsulation/VertexBuffer.h"

class Terrain
{
private:
    std::vector<float>  _vertices;
    Layout              _bufferLayout;
    std::vector<Element> _elements;
    Shader              _shader;

public:
    Terrain(const std::string &, const std::string &);

    void    bindTerrain();
};

#endif //INC_71K2LEDEB_TERRAIN_H
