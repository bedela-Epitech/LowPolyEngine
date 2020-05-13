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
    FrameBuffer             _fbo;
    std::shared_ptr<Terrain>    _terrain;
public:
    ShadowMap(const std::shared_ptr<Terrain> &, const std::string &, const std::string &, const glm::vec2 &, const glm::vec2 &, bool , bool , int , int);
    void    draw();
};

#endif //LOWPOLYENGINE_SHADOWMAP_H
