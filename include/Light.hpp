//
// Created by adrien on 03/01/20.
//

#ifndef _LEDEB_LIGHT_HPP_
#define _LEDEB_LIGHT_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{

public:
	glm::vec3   _lightDir{0, 1, 0};
	glm::vec3   _lightColor{1, 1, 1};
	float       _specularStrenght = 0.5f;
    float       _ambiantCoeff = 0.3f;

public:
	Light() = default;

	void setDir(const glm::vec3 &);
	void setColor(const glm::vec3 &);
	void setAmbient(float);
	void setSpecular(float);

};

#endif // !_LEDEB_LIGHT_HPP_