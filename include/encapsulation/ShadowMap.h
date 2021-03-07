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

public:
    ShadowMap(const std::string &, const std::string &, bool , bool , int , int);
    void    draw(const std::unique_ptr<Terrain> &);
    void    updateShader(const glm::mat4 &);
};

#endif //LOWPOLYENGINE_SHADOWMAP_H
