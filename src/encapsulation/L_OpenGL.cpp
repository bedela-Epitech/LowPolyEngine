
#include "encapsulation/L_OpenGL.hpp"

/////////////////////
//
//	INIT
//
/////////////////////

L_OpenGL::L_OpenGL(Camera *camera)
{
	_camera = camera;
	_light.setPos(31.0, 35.0, 73.0, 1.0);
	_light.setDiffuse(0.0, 0.0, 1.0, 1.0);
	_light.setAmbient(0.0, 0.0, 0.0, 1.0);
	_light.setSpecular(1.0, 1.0, 1.0, 1.0);

	_light2.setPos(20.0, 5.0, 20.0, 1.0);
	_light2.setDiffuse(1.0, 0.0, 0.0, 1.0);
	_light2.setAmbient(0.0, 0.0, 0.0, 1.0);
	_light2.setSpecular(1.0, 1.0, 1.0, 1.0);
}

void	L_OpenGL::init()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void	L_OpenGL::initReshape(sf::RenderWindow &window)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int x = window.getSize().x;
	int y = window.getSize().y;
	glViewport(0, 0, x, y);
	gluPerspective(60, (float)x / (float)y, 0.1f, 2512.f);
	glMatrixMode(GL_MODELVIEW);
}

void	L_OpenGL::initLights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_POSITION, _light._pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _light._diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, _light._ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _light._specular);

	/*glLightfv(GL_LIGHT1, GL_POSITION, _light2._pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, _light2._diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, _light2._ambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, _light2._specular);*/
}

/////////////////////
//
//	RUNTIME	
//
/////////////////////

void	L_OpenGL::clear()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	L_OpenGL::updateCamera()
{
	glLoadIdentity();

	glRotatef(0.0f + _camera->_rotate.x, 1.0, 0.0, 0.0);
	glRotatef(0.0f + _camera->_rotate.y, 0.0, 1.0, 0.0);


	glTranslatef(0.f - _camera->_move.x, -5.f, -3.f - _camera->_move.z);

	glPushMatrix();

	gluLookAt(0.f, 0.f, -3.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
}

void	L_OpenGL::initRendering()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	initLights();
}

void	L_OpenGL::render(GLfloat tete[], Vector3df &normal)
{
	glNormal3f(normal.x, normal.y, normal.z);
	glVertexPointer(3, GL_FLOAT, 0, tete);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void	L_OpenGL::finishRendering()
{
	switchOfLights();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

/////////////////////
//
//	fINISH	
//
/////////////////////


L_OpenGL::~L_OpenGL()
{

}

void	L_OpenGL::switchOfLights()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
}

void	L_OpenGL::resetReshap()
{
	glPopMatrix();

	GLenum err = glGetError();
}
