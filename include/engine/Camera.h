
#ifndef		_LEDEB_CAMERA_H_
#define		_LEDEB_CAMERA_H_

#include "encapsulation/Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    float               _fov;
    float               _screenRatio;
    float               _near;
    float               _far;
    glm::mat4           _projection;

	glm::vec3	_cameraPos;
	glm::vec3	_cameraUp;
    glm::vec3	_dirLook;
    glm::mat4	_view;

    float       _rotateX = 0.f;
    float       _rotateY = 0.f;
    float       _upAngleLimit = 89.9f;
    float       _downAngleLimit = -89.9f;

    float       _translationCelerity = 150.f;
    float       _rotationCelerity = 60.f;

public:
	Camera(float, float, float, float, float, float, float, float, float);

    void	closeWindow(float);

    void	moveLeft(float);
	void	moveRight(float);
	void	moveForward(float);
	void	moveBack(float);

	void	rotateLeft(float);
	void	rotateRight(float);
	void	rotateUp(float);
	void	rotateDown(float);

    void    setFov(float);
    void    setScreenRatio(float);
    void    setNear(float);
    void    setFar(float);
    void    setProjection(const glm::mat4 &);


    void    updateCamera();

private:
    void    updateProjection();

};

#endif		// !_LEDEB_CAMERA_H_


