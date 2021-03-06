//
// Created by bedela on 13/05/2020.
//

#ifndef LOWPOLYENGINE_SHADOWMAP_H
#define LOWPOLYENGINE_SHADOWMAP_H

#include <memory>
#include "encapsulation/FrameBuffer.h"
#include "map/Terrain.h"

class ShadowMap
{
public:
    Shader          _shader;
    FrameBuffer     _fbo;
    std::shared_ptr<Terrain>    _terrain;

public:
    ShadowMap(const std::string &, const std::string &, const std::shared_ptr<Terrain> &, bool , bool , int , int);
    void    draw();
    void    updateShader(const glm::mat4 &);
};

#endif //LOWPOLYENGINE_SHADOWMAP_H
