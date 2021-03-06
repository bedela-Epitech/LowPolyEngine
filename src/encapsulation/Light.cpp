//
// Created by bedela on 13/05/2020.
//

#include "encapsulation/Light.h"

Light::Light()
{
    _bias = glm::mat4(
            0.5, 0.0, 0.0, 0.0,
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
    );
    _lightDir = glm::normalize(_lightDir);
}

glm::mat4    doRotation(glm::vec3 v1, glm::vec3 v2)
{
    v1 = glm::normalize(v1);
    v2 = glm::normalize(v2);
    glm::vec3 v = glm::cross(v2, v1);
    float angle = acos(glm::dot(v2, v1) / (glm::length(v2) * glm::length(v1)));
    glm::mat4 rotmat = glm::mat4(1.0);
    if (glm::dot(v2, v1) == 1)
        return rotmat;
    rotmat = glm::rotate(rotmat, angle, v);
    return rotmat;
}

void Light::updateLight(std::shared_ptr<Camera> camera)
{
    glm::mat4 rot = doRotation(camera->_cameraLook, glm::vec3(0, 0, 1));

    float tanFov = tanf(((camera->_fov / 2.f) * (float)M_PI) / 180.f);

    float heightNear = tanFov * camera->_near;
    float widthNear = heightNear * camera->_screenRatio;

    float heightFar = tanFov * (camera->_far / 10.f);
    float widthFar = heightFar * camera->_screenRatio;

    glm::vec3 centerNear = camera->_cameraPos + camera->_cameraLook * camera->_near;
    glm::vec3 centerFar = camera->_cameraPos + camera->_cameraLook * (camera->_far / 10.f);

    auto nearTopLeft = centerNear + camera->_cameraUp * heightNear + camera->_cameraRight * -widthNear;
    auto nearTopRight = centerNear + camera->_cameraUp * heightNear + camera->_cameraRight * widthNear;
    auto nearBottomLeft = centerNear + camera->_cameraUp * -heightNear + camera->_cameraRight * -widthNear;
    auto nearBottomRight = centerNear + camera->_cameraUp * -heightNear + camera->_cameraRight * widthNear;

    auto farTopLeft = centerFar + camera->_cameraUp * heightFar + camera->_cameraRight * -widthFar;
    auto farTopRight = centerFar + camera->_cameraUp * heightFar + camera->_cameraRight * widthFar;
    auto farBottomLeft = centerFar + camera->_cameraUp * -heightFar + camera->_cameraRight * -widthFar;
    auto farBottomRight = centerFar + camera->_cameraUp * -heightFar + camera->_cameraRight * widthFar;

    glm::vec3 sun(-1, -1, 0);
    glm::mat4 rotBackSun = doRotation(sun, glm::vec3(0, 0, 1));
    glm::mat4 rotSun = doRotation(glm::vec3(0, 0, 1), sun);


    glm::vec3 array[8];

    array[0] = rotSun * glm::vec4(nearTopLeft, 1.0);
    array[1] = rotSun * glm::vec4(nearTopRight, 1.0);
    array[2] = rotSun * glm::vec4(nearBottomLeft, 1.0);
    array[3] = rotSun * glm::vec4(nearBottomRight, 1.0);

    array[4] = rotSun * glm::vec4(farTopLeft, 1.0);
    array[5] = rotSun * glm::vec4(farTopRight, 1.0);
    array[6] = rotSun * glm::vec4(farBottomLeft, 1.0);
    array[7] = rotSun * glm::vec4(farBottomRight, 1.0);

    float minX = array[0].x;
    float minY = array[0].y;
    float minZ = array[0].z;
    float maxX = array[0].x;
    float maxY = array[0].y;
    float maxZ = array[0].z;
    glm::vec3 centroid(0, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        minX = std::min(minX, array[i].x);
        minY = std::min(minY, array[i].y);
        minZ = std::min(minZ, array[i].z);
        maxX = std::max(maxX, array[i].x);
        maxY = std::max(maxY, array[i].y);
        maxZ = std::max(maxZ, array[i].z);
    }
    centroid.x = (maxX + minX) / 2.f;
    centroid.y = (maxY + minY) / 2.f;
    centroid.z = (maxZ + minZ) / 2.f;
    _centroid = rotBackSun * glm::vec4(centroid, 1.0);
    _width = maxX - minX;
    _height = maxY - minY;
    _deep = maxZ - minZ;

    // Compute the MVP matrix from the light's point of view
    glm::mat4 lightProjectionMatrix = glm::ortho<float>(_width * -0.7f, _width * 0.7f,
                                                        _height * -0.7f, _height * 0.7f,
                                                        _deep * -0.7f, _deep * 0.7f);
    glm::mat4 lightViewMatrix = glm::lookAt(_centroid, _centroid + glm::vec3(-1, -1, 0) , glm::vec3(0, 1, 0));
    _mvp = lightProjectionMatrix * lightViewMatrix;
}

glm::mat4 Light::getBiasLightMvp() const
{
    return (_bias * _mvp);
}

void Light::setDir(const glm::vec3 &dir)
{
    _lightDir = dir;
}

void Light::setColor(const glm::vec3 &color)
{
    _lightColor = color;
}

void Light::setAmbient(float ambiant)
{
    _ambiantCoeff = ambiant;
}

void Light::setSpecular(float specular)
{
    _specularStrenght = specular;
}