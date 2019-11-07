
#ifndef _LEDEB_LIGHT_HPP_
#define _LEDEB_LIGHT_HPP_

#include "GL/glut.h"


class Light
{

public:
	GLfloat _pos[4];
	GLfloat _diffuse[4];
	GLfloat _ambient[4];
	GLfloat _specular[4];

public:
	Light();
	~Light();

	void setPos(const float &r, const float &g, const float &b, const float &a);
	void setDiffuse(const float &r, const float &g, const float &b, const float &a);
	void setAmbient(const float &r, const float &g, const float &b, const float &a);
	void setSpecular(const float &r, const float &g, const float &b, const float &a);

};

#endif // !_LEDEB_LIGHT_HPP_