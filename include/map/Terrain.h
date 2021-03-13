//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_TERRAIN_H
#define INC_71K2LEDEB_TERRAIN_H

#include <future>
#include "tool/ModelCreator.h"
#include "engine/Camera.h"
#include "encapsulation/Shader.h"
#include "encapsulation/Light.h"
#include "map/QuadTree.h"
#include "encapsulation/VertexArray.h"

class Terrain
{
public:
    QuadTree            _qt;
    Shader              _shader;
    bool                _isTerrainReady = false;
    bool                _isTerrainLinked = false;
    VertexArray         _vArray;
    unsigned int        _vertexNb;
    std::thread         _loadingThread;
    glm::mat4           _mvp;

private:
    std::vector<float>  _vertices;
    Layout              _bufferLayout;
    unsigned int        _size;

public:
    Terrain(const std::string &, const std::string &);

    void    generateTerrain();
    void    bindTerrain(const std::unique_ptr<Light> &);
    void    draw() const;

    void    update(const std::unique_ptr<Camera> &, const glm::mat4&, unsigned int);
    void    modifyTerrain();

private:
    void    updatePos(const glm::vec3 &);
};

#endif //INC_71K2LEDEB_TERRAIN_H
