

#ifndef _L_OPENGL_HPP_

#define _L_OPENGL_HPP_

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GL/glut.h"

#include "TypeDef.hpp"
#include "engine/Camera.hpp"
#include "Light.hpp"

class L_OpenGL
{

private:
	Camera * _camera;
	Light _light;
	Light _light2;

public:
	L_OpenGL(Camera *camera);
	~L_OpenGL();

	void	clear();
	void	switchOfLights();
	void	initLights();
	void	render(GLfloat tete[], Vector3df &normal);
	void	initReshape(sf::RenderWindow &window);
	void	resetReshap();
	void	updateCamera();
	void	init();
	void	finishRendering();
	void	initRendering();

};

#endif // _L_OPENGL_HPP_
