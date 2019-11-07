
#include "Light.hpp"

Light::Light()
{
}

Light::~Light()
{
}


void Light::setPos(const float &r, const float &g, const float &b, const float &a)
{
	_pos[0] = r;
	_pos[1] = g;
	_pos[2] = b;
	_pos[3] = a;
}

void Light::setDiffuse(const float &r, const float &g, const float &b, const float &a)
{
	_diffuse[0] = r;
	_diffuse[1] = g;
	_diffuse[2] = b;
	_diffuse[3] = a;
}

void Light::setAmbient(const float &r, const float &g, const float &b, const float &a)
{
	_ambient[0] = r;
	_ambient[1] = g;
	_ambient[2] = b;
	_ambient[3] = a;
}

void Light::setSpecular(const float &r, const float &g, const float &b, const float &a)
{
	_specular[0] = r;
	_specular[1] = g;
	_specular[2] = b;
	_specular[3] = a;
}
