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
private:
    glm::mat4       _bias;
    
public:
    Shader          _shader;
    FrameBuffer     _fbo;
    glm::mat4       _lightMvp;
    std::shared_ptr<Terrain>    _terrain;

public:
    ShadowMap(const std::string &, const std::string &, const std::shared_ptr<Terrain> &, bool , bool , int , int);
    void    draw();
    void    updateShader(std::shared_ptr<Camera>);
    [[nodiscard]] glm::mat4   getBiasLightMvp() const;
};

#endif //LOWPOLYENGINE_SHADOWMAP_H
