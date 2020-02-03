

#ifndef _L_OPENGL_HPP_

#define _L_OPENGL_HPP_

#include <vector>
#include "Shader.h"
#include "Light.hpp"
#include "map/QuadTree.h"
#include <future>

class L_OpenGL
{
public:
    std::thread         _loadingThread;

    Shader              _mapShader;
    Shader              _textShader;
    Light               _light;

    std::vector<float>  _mapVertices;
    std::vector<float>  _textVertices;

    unsigned int        _mapVBO;
    unsigned int        _mapVAO;

    unsigned int        _textVBO;
    unsigned int        _textVAO;

    bool                _isMapReady = false;
    bool                _linkDone = false;

public:
    L_OpenGL(const std::string &, const std::string &,
             const std::string &, const std::string &);

    void    linkTerrainInfo();
    void    linkTextureInfo();

    void    generateTerrain();
    void    initTexture();

    void    initShader(const glm::mat4 &);
    void    updateShader(const glm::vec3 &, const glm::mat4 &);

    void    display();
    void    cleanUp();

    void setTexture(int);
    void setDir(const glm::vec3 &);
    void setColor(const glm::vec3 &);
    void setAmbient(float);
    void setSpecular(float);
};

#endif // _L_OPENGL_HPP_
