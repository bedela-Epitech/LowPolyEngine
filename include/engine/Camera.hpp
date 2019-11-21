
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
	Camera(const glm::ivec2 &, float, float, float, float, float, float, float, float, float);

    void	closeWindow(GLFWwindow *, const float &speed);

    void	moveLeft(GLFWwindow *, const float &speed);
	void	moveRight(GLFWwindow *, const float &speed);
	void	moveForward(GLFWwindow *, const float &speed);
	void	moveBack(GLFWwindow *, const float &speed);

	void	rotateLeft(GLFWwindow *, const float &speed);
	void	rotateRight(GLFWwindow *, const float &speed);
	void	rotateUp(GLFWwindow *, const float &speed);
	void	rotateDown(GLFWwindow *, const float &speed);

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


