
#include "encapsulation/Light.h"

Light::Light()
{
    _lightDir = glm::normalize(_lightDir);
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