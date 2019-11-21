
#ifndef		_LEDEB_CAMERA_HPP_
#define		_LEDEB_CAMERA_HPP_

#include "encapsulation/Window.hpp"

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

    float       _translationCelerity = 1.5f;

public:
	Camera(float, float, float, float, float, float, float, float, float);

    void	closeWindow(const float &speed);

    void	moveLeft(const float &speed);
	void	moveRight(const float &speed);
	void	moveForward(const float &speed);
	void	moveBack(const float &speed);

	void	rotateLeft(const float &speed);
	void	rotateRight(const float &speed);
	void	rotateUp(const float &speed);
	void	rotateDown(const float &speed);

    void    setFov(float);
    void    setScreenRatio(float);
    void    setNear(float);
    void    setFar(float);
    void    setProjection(const glm::mat4 &);


    void    updateCamera();

private:
    void    updateProjection();

};

#endif		// !_LEDEB_CAMERA_HPP_


