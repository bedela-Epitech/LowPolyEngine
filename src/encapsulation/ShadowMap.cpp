//
// Created by bedela on 13/05/2020.
//

#include "encapsulation/ShadowMap.h"

ShadowMap::ShadowMap(const std::shared_ptr<Terrain> &terrain, const std::string &textVsPath, const std::string &textFsPath, const glm::vec2 &pos, const glm::vec2 &size,
                     bool needImage, bool needDepth, int width, int height)
                     : _terrain(terrain), _fbo(textVsPath, textFsPath, pos, size, needImage, needDepth, width, height)
{

}

void ShadowMap::draw()
{
    _fbo.bind();
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    _terrain->draw();
    _fbo.unbind();

    _fbo._gui._textShader.use();
    _fbo._imageTexture.bind();
    _fbo._gui.draw();
}