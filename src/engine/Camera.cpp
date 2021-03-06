//
// Created by bedela on 13/05/2020.
//

#include "engine/Camera.h"

/////////////////////
//
//	INITIALIZE	
//
/////////////////////

Camera::Camera(float cameraX, float cameraY, float cameraZ)
        : _cameraPos({cameraX, cameraY, cameraZ})
{
    _fov = 60.f;
    _screenRatio = Window::getScreenRatio();
    _near = 0.1f;
    _far = 10040.f;
    _projection = glm::perspective(glm::radians(_fov), _screenRatio, _near, _far);
    // invert x for left handed coordinate system
    _projection = glm::scale(_projection, glm::vec3(-1, 1, 1));
}

/////////////////////
//
//	CAMERA
//
/////////////////////


void    Camera::updateCamera()
{
    _cameraLook = glm::vec3(sin(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)),
                            sin(glm::radians(_rotateX)),
                         cos(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)));
    _cameraRight = glm::normalize(glm::cross({0.0f, 1.0f, 0.0f}, _cameraLook));
    _cameraUp = glm::cross(_cameraLook, _cameraRight);

    _view = glm::lookAt(_cameraPos, _cameraPos + _cameraLook, _cameraUp);
}

/////////////////////
//
//	WINDOW
//
/////////////////////

void	Camera::closeWindow(float speed)
{
    Window::close();
}

/////////////////////
//
//	MOVE	
//
/////////////////////

void	Camera::moveLeft(float deltaTime)
{
    _cameraPos -= _translationCelerity * deltaTime * glm::normalize(glm::cross(_cameraUp, _cameraLook));
}

void	Camera::moveRight(float deltaTime)
{
    _cameraPos += _translationCelerity * deltaTime * glm::normalize(glm::cross(_cameraUp, _cameraLook));
}

void	Camera::moveBack(float deltaTime)
{
    _cameraPos -= _translationCelerity * deltaTime * _cameraLook;
}

void	Camera::moveForward(float deltaTime)
{
    _cameraPos += _translationCelerity * deltaTime * _cameraLook;
}

/////////////////////
//
//	ROTATE	
//
/////////////////////

void	Camera::rotateLeft(float deltaTime)
{
    _rotateY -= _rotationCelerity * deltaTime;
}

void	Camera::rotateRight(float deltaTime)
{
    _rotateY += _rotationCelerity * deltaTime;
}

void	Camera::rotateUp(float deltaTime)
{
    _rotateX += _rotationCelerity * deltaTime;
    _rotateX = std::min(std::max(_downAngleLimit, _rotateX), _upAngleLimit);
}

void	Camera::rotateDown(float deltaTime)
{
    _rotateX -= _rotationCelerity * deltaTime;
    _rotateX = std::min(std::max(_downAngleLimit, _rotateX), _upAngleLimit);
}