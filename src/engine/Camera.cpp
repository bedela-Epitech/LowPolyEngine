
#include "engine/Camera.hpp"
#include <iostream>

/////////////////////
//
//	INITIALIZE	
//
/////////////////////

Camera::Camera() : _move(Vector3df(0, 0, 0)), _rotate(Vector3df(0, 0, 0))
{
}

Camera::~Camera()
{
}

/////////////////////
//
//	MOVE	
//
/////////////////////

void	Camera::moveLeft(const float &speed)
{
	_move += Vector3df(cos((_rotate.y / 180) * 3.14f) * speed, 0.0f, sin((_rotate.y / 180) * 3.14f) * speed);
}

void	Camera::moveRight(const float &speed)
{
	_move -= Vector3df(cos((_rotate.y / 180) * 3.14f) * speed, 0.0f, sin((_rotate.y / 180) * 3.14f) * speed);
}

void	Camera::moveBack(const float &speed)
{
	_move += Vector3df(sin((_rotate.y / 180) * 3.14f) * speed, 0.0f, cos((_rotate.y / 180) * 3.14f) * speed * -1);
}

void	Camera::moveForward(const float &speed)
{
	_move += Vector3df(sin((_rotate.y / 180) * 3.14f) * speed * -1, 0.0f, cos((_rotate.y / 180) * 3.14f) * speed);
}

/////////////////////
//
//	ROTATE	
//
/////////////////////

void	Camera::rotateLeft(const float &speed)
{
	_rotate.y--;
}

void	Camera::rotateRight(const float &speed)
{
	_rotate.y++;
}

void	Camera::rotateUp(const float &speed)
{
	_rotate.x++;
}

void	Camera::rotateDown(const float &speed)
{
	_rotate.x--;
}