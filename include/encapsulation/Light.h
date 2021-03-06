//
// Created by adrien on 03/01/20.
//

#ifndef _LEDEB_LIGHT_H_
#define _LEDEB_LIGHT_H_

#include <memory>
#include "engine/Camera.h"

class Light
{
private:
    glm::mat4       _bias;

public:
    glm::mat4       _mvp;

    glm::vec3 _centroid;
    float _width;
    float _height;
    float _deep;

    glm::vec3   _lightDir{-1, -1, 0};
	glm::vec3   _lightColor{1, 1, 1};
	float       _specularStrenght = 0.5f;
    float       _ambiantCoeff = 0.3f;

public:
	Light();

	void updateLight(std::shared_ptr<Camera>);
    glm::mat4 getBiasLightMvp() const;

	void setDir(const glm::vec3 &);
	void setColor(const glm::vec3 &);
	void setAmbient(float);
	void setSpecular(float);

};

#endif // !_LEDEB_LIGHT_H_