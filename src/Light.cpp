
#include "Light.hpp"

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