
#include "engine/Camera.hpp"
#include <iostream>

/////////////////////
//
//	INITIALIZE	
//
/////////////////////

Camera::Camera(float cameraX,  float cameraY, float cameraZ,
               float cameraUpX, float cameraUpY, float cameraUpZ,
               float dirLookX, float dirLookY, float dirLookZ)
        : _cameraPos(glm::vec3(cameraX, cameraY, cameraZ)),
          _cameraUp(glm::vec3(cameraUpX, cameraUpY, cameraUpZ)),
          _dirLook(glm::vec3(dirLookX, dirLookY, dirLookZ))
{
    _fov = 60.f;
    _screenRatio = Window::getScreenRatio();
    _near = 0.1f;
    _far = 10240.f;
    _projection = glm::perspective(glm::radians(_fov), _screenRatio, _near, _far);
    _projection = glm::scale(_projection, glm::vec3(-1, 1, 1));
}

/////////////////////
//
//	CAMERA
//
/////////////////////

void    Camera::updateCamera()
{

    _dirLook = glm::vec3(sin(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)),
                         sin(glm::radians(_rotateX)),
                         cos(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)));

    _view = glm::lookAt(_cameraPos, _cameraPos + _dirLook, _cameraUp);
}

/////////////////////
//
//	SETTERS
//
/////////////////////

void    Camera::setFov(float fov)
{
    _fov = fov;
    updateProjection();
}

void    Camera::setScreenRatio(float screenratio)
{
    _screenRatio = screenratio;
    updateProjection();
}

void    Camera::setNear(float near)
{
    _near = near;
    updateProjection();
}

void    Camera::setFar(float far)
{
    _far = far;
    updateProjection();
}

void    Camera::setProjection(const glm::mat4 &projection)
{
    _projection = projection;
}

void    Camera::updateProjection()
{
    _projection = glm::perspective(glm::radians(_fov), _screenRatio, _near, _far);
}

/////////////////////
//
//	WINDOW
//
/////////////////////

void	Camera::closeWindow(float speed)
{
    glfwSetWindowShouldClose(Window::_window, true);
}

/////////////////////
//
//	MOVE	
//
/////////////////////

void	Camera::moveLeft(float deltaTime)
{
    _cameraPos -= _translationCelerity * _cameraSpeed * deltaTime * glm::normalize(glm::cross(_cameraUp, _dirLook));
}

void	Camera::moveRight(float deltaTime)
{
    _cameraPos += _translationCelerity * _cameraSpeed * deltaTime * glm::normalize(glm::cross(_cameraUp, _dirLook));
}

void	Camera::moveBack(float deltaTime)
{
    _cameraPos -= _translationCelerity * _cameraSpeed * deltaTime * _dirLook;
}

void	Camera::moveForward(float deltaTime)
{
    _cameraPos += _translationCelerity * _cameraSpeed * deltaTime * _dirLook;
}

/////////////////////
//
//	ROTATE	
//
/////////////////////

void	Camera::rotateLeft(float deltaTime)
{
    _rotateY -= _translationCelerity * 40.f * deltaTime;
}

void	Camera::rotateRight(float deltaTime)
{
    _rotateY += _translationCelerity * 40.f * deltaTime;
}

void	Camera::rotateUp(float deltaTime)
{
    _rotateX += _translationCelerity * 40.f * deltaTime;
    _rotateX = std::min(std::max(_downAngleLimit, _rotateX), _upAngleLimit);
}

void	Camera::rotateDown(float deltaTime)
{
    _rotateX -= _translationCelerity * 40.f * deltaTime;
    _rotateX = std::min(std::max(_downAngleLimit, _rotateX), _upAngleLimit);
}