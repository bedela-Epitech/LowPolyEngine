//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_TERRAIN_H
#define INC_71K2LEDEB_TERRAIN_H

#include "encapsulation/Shader.h"
#include "encapsulation/Light.h"
#include "map/QuadTree.h"
#include "encapsulation/VertexArray.h"

class Terrain
{
public:
    Shader              _shader;
    bool                _isTerrainReady = false;
    bool                _isTerrainLinked = false;
    VertexArray         _vArray;
    unsigned int        _vertexNb;
private:
    Light               _sun;
    std::vector<float>  _vertices;
    Layout              _bufferLayout;

public:
    Terrain(const std::string &, const std::string &);

    void    generateTerrain();
    void    bindTerrain();

    // sun manager
    void setDir(const glm::vec3 &);
    void setColor(const glm::vec3 &);
    void setAmbient(float);
    void setSpecular(float);
};

#endif //INC_71K2LEDEB_TERRAIN_H
