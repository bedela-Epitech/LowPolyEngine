//
// Created by bedela on 13/05/2020.
//

#include "encapsulation/ShadowMap.h"

ShadowMap::ShadowMap(const std::string &shadowVsPath,
                     const std::string &shadowFsPath, const std::shared_ptr<Terrain> &terrain,
                     bool needImage, bool needDepth, int width, int height)
        : _shader(shadowVsPath, shadowFsPath), _terrain(terrain), _fbo(needImage, needDepth, width, height)
{ }

void ShadowMap::draw()
{
    _shader.use();
    _fbo.bind();
    glEnable(GL_DEPTH_TEST);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    _terrain->draw();
    _fbo.unbind();
}

void ShadowMap::updateShader(const glm::mat4 &lightMvp)
{
    _shader.use();
    _shader.setMat4("lightmvp", lightMvp);
}