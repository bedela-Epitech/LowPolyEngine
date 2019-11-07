
#ifndef		_LEDEB_CAMERA_HPP_
#define		_LEDEB_CAMERA_HPP_

#include "TypeDef.hpp"

class Camera
{
public:
	Vector3df	_move;
	Vector3df	_rotate;

public:
	Camera();
	~Camera();

	void	moveLeft(const float &speed);
	void	moveRight(const float &speed);
	void	moveForward(const float &speed);
	void	moveBack(const float &speed);

	void	rotateLeft(const float &speed);
	void	rotateRight(const float &speed);
	void	rotateUp(const float &speed);
	void	rotateDown(const float &speed);

};

#endif		// !_LEDEB_CAMERA_HPP_


