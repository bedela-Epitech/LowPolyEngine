
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
//	WINDOW
//
/////////////////////

void	Camera::closeWindow(GLFWwindow *window, const float &speed)
{
    glfwSetWindowShouldClose(window, true);
}

/////////////////////
//
//	MOVE	
//
/////////////////////

void	Camera::moveLeft(GLFWwindow *window, const float &speed)
{
    _cameraPos += _translationCelerity * 100.f * speed * glm::normalize(glm::cross(_cameraUp, _dirLook));
}

void	Camera::moveRight(GLFWwindow *window, const float &speed)
{
    _cameraPos -= _translationCelerity * 100.f * speed * glm::normalize(glm::cross(_cameraUp, _dirLook));
}

void	Camera::moveBack(GLFWwindow *window, const float &speed)
{
    _cameraPos -= _translationCelerity * 100.f * speed * _dirLook;
}

void	Camera::moveForward(GLFWwindow *window, const float &speed)
{
    _cameraPos += _translationCelerity * 100.f * speed * _dirLook;
}

/////////////////////
//
//	ROTATE	
//
/////////////////////

void	Camera::rotateLeft(GLFWwindow *window, const float &speed)
{
    _rotateY += _translationCelerity * 40.f * speed;
}

void	Camera::rotateRight(GLFWwindow *window, const float &speed)
{
    _rotateY -= _translationCelerity * 40.f * speed;
}

void	Camera::rotateUp(GLFWwindow *window, const float &speed)
{
    _rotateX += _translationCelerity * 40.f * speed;
    _rotateX = std::min(std::max(_downAngleLimit, _rotateX), _upAngleLimit);
}

void	Camera::rotateDown(GLFWwindow *window, const float &speed)
{
    _rotateX -= _translationCelerity * 40.f * speed;
    _rotateX = std::min(std::max(_downAngleLimit, _rotateX), _upAngleLimit);
}