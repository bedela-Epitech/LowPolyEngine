//
// Created by adrien on 03/01/20.
//

#ifndef INC_71K2LEDEB_TERRAIN_H
#define INC_71K2LEDEB_TERRAIN_H

#include <future>
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
    std::thread         _loadingThread;
    glm::mat4           _projection;
    glm::mat4           _mvp;
private:
    //toremove
    int                 _idxEnd;
    Light               _sun;
    std::vector<float>  _vertices;
    Layout              _bufferLayout;

public:
    Terrain(const std::string &, const std::string &);

    void    generateTerrain();
    void    bindTerrain();
    void    draw() const;
    void    changeCamCorner(const std::vector<glm::vec3> &);

    void    modifyTerrain();

    std::vector<float>  getCube(const glm::vec3 &, float size);
    std::vector<float>  getTriangle(const std::vector<glm::vec3> &, const glm::vec3 &, const glm::vec3 &);
    // sun manager
    void setDir(const glm::vec3 &);
    void setColor(const glm::vec3 &);
    void setAmbient(float);
    void setSpecular(float);
};

#endif //INC_71K2LEDEB_TERRAIN_H
