
#ifndef		_LEDEB_CAMERA_H_
#define		_LEDEB_CAMERA_H_

#include "encapsulation/Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Camera
{
public:
    float       _fov;
    float       _screenRatio;
    float       _near;
    float       _far;
    glm::mat4   _projection;
    glm::mat4	_view;

    glm::vec3	_cameraPos;
    glm::vec3	_cameraRight{1, 0, 0};
    glm::vec3	_cameraUp{0, 1, 0};
    glm::vec3	_cameraLook{0, 0, 1};


    float       _rotateX = 0.f;
    float       _rotateY = 0.f;
    float       _upAngleLimit = 89.9f;
    float       _downAngleLimit = -89.9f;

    float       _translationCelerity = 1050.f;
    float       _rotationCelerity = 60.f;

public:
	Camera(float, float, float);

    void	closeWindow(float);

    void	moveLeft(float);
	void	moveRight(float);
	void	moveForward(float);
	void	moveBack(float);

	void	rotateLeft(float);
	void	rotateRight(float);
	void	rotateUp(float);
	void	rotateDown(float);

    void    updateCamera();

};

#endif		// !_LEDEB_CAMERA_H_


