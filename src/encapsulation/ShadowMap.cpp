//
// Created by bedela on 13/05/2020.
//

#include "encapsulation/ShadowMap.h"

ShadowMap::ShadowMap(const std::string &shadowVsPath,
                     const std::string &shadowFsPath, const std::shared_ptr<Terrain> &terrain,
                     bool needImage, bool needDepth, int width, int height)
        : _shader(shadowVsPath, shadowFsPath), _terrain(terrain), _fbo(needImage, needDepth, width, height)
{
    _bias = glm::mat4(
            0.5, 0.0, 0.0, 0.0,
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
    );
}

void ShadowMap::draw()
{
    _shader.use();
    _fbo.bind();
    glEnable(GL_DEPTH_TEST);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    _terrain->draw();
    _fbo.unbind();
}

void ShadowMap::updateShader(std::shared_ptr<Camera> camera)
{
    _shader.use();
    // Compute the MVP matrix from the light's point of view
    glm::mat4 lightProjectionMatrix = glm::ortho<float>(camera->_width * -0.7f, camera->_width * 0.7f,
                                                        camera->_height * -0.7f, camera->_height * 0.7f,
                                                        camera->_deep * -0.7f, camera->_deep * 0.7f);
    glm::mat4 lightViewMatrix = glm::lookAt(camera->_centroid, camera->_centroid + glm::vec3(-1, -1, 0) , glm::vec3(0, 1, 0));
    _lightMvp = lightProjectionMatrix * lightViewMatrix;

    _shader.setMat4("lightmvp", _lightMvp);
}

glm::mat4 ShadowMap::getBiasLightMvp() const
{
    return (_bias * _lightMvp);
}