//
// main.cpp for  in /home/vagrant/shared_data/Bedel2K17
// 
// Made by Vagrant Default User
// Login   <adrien.bedel@epitech.eu>
// 
// Started on  Mon Mar 27 16:54:35 2017 Vagrant Default User
// Last update Mon Mar 27 16:55:53 2017 Vagrant Default User
//


#include "encapsulation/Input.hpp"

#include "GL/glut.h"
#include "encapsulation/L_OpenGL.hpp"
#include <iostream>
#include <vector>
#include "Triangle.hpp"
#include "engine/ObjParser.hpp"
#include "Light.hpp"

#include "map/Diamond.hpp"


void draw(std::vector<game::Triangle<float> > &triangles, L_OpenGL &gl)
{
	gl.initRendering();

	GLfloat tete[9];

	for (size_t k = 0; k < triangles.size(); k++)
	{
		tete[0] = triangles[k].vertices[0].x;
		tete[1] = triangles[k].vertices[0].y;
		tete[2] = triangles[k].vertices[0].z;

		tete[3] = triangles[k].vertices[1].x;
		tete[4] = triangles[k].vertices[1].y;
		tete[5] = triangles[k].vertices[1].z;

		tete[6] = triangles[k].vertices[2].x;
		tete[7] = triangles[k].vertices[2].y;
		tete[8] = triangles[k].vertices[2].z;

		gl.render(tete, triangles[k].normal);
	}
	gl.finishRendering();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 540), "Cube!", sf::Style::Default);
	Camera *camera = new Camera();
	L_OpenGL gl(camera);
	Input input(camera);

	Diamond diams(0.75f, 65);
	diams.fillMap();
	diams.updateVertices(5, 250);
	diams.updateTriangles();
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
	window.resetGLStates();
	//game::Parser parser("../ressources/obj/hazelnut.obj");
	diams.printMap();
	std::vector<game::Triangle<float>>	terrain;
	gl.init();

	gl.initReshape(window);

	bool running = true;
	while (running)
	{
		while (window.pollEvent(input._event))
		{
			input.KeyManager(running);
		}
		input.KeyManager(running);

		gl.clear();

		gl.updateCamera();

		//draw(parser.triangles, gl);
		draw(diams._triangles, gl);
		window.display();
	}
	gl.resetReshap();
	return 0;
}