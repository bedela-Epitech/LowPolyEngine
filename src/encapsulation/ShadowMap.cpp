//
// Created by bedela on 13/05/2020.
//

#include "encapsulation/ShadowMap.h"

ShadowMap::ShadowMap(const std::string &shadowVsPath,
                     const std::string &shadowFsPath, const std::shared_ptr<Terrain> &terrain, const std::string &textVsPath,
                     const std::string &textFsPath, const glm::vec2 &pos, const glm::vec2 &size,
                     bool needImage, bool needDepth, int width, int height)
        : _shader(shadowVsPath, shadowFsPath), _gui(textVsPath, textFsPath, pos, size), _terrain(terrain), _fbo(needImage, needDepth, width, height)
{
    glm::vec3 lightInvDir = glm::vec3(50, 30, 50);

    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,40);
    glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    _shader.use();
    _shader.setMat4("mvp", depthMVP);

    _gui.attachTexture(_fbo._depthTexture);

}

void ShadowMap::draw()
{
    _shader.use();
    _fbo.bind();
    glEnable(GL_DEPTH_TEST);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    _terrain->draw();
    _fbo.unbind();

    _gui._textShader.use();
    _fbo._depthTexture.bind();
    _gui.draw();
}