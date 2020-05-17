
#include "engine/Camera.h"
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

glm::mat4    doRotation(glm::vec3 v1, glm::vec3 v2)
{
    glm::vec3 a = glm::cross(v1, v2);
    glm::vec4 q;

    float dot = glm::dot(v1, v2);

    float s = sqrt( (1+dot)*2 );
    float invs = 1 / s;

    glm::vec3 c = glm::cross(v1, v2);

    q.x = c.x * invs;
    q.y = c.y * invs;
    q.z = c.z * invs;
    q.w = s * 0.5f;
    q = glm::normalize(q);


    v1 = glm::normalize(v1);
    v2 = glm::normalize(v2);
    glm::vec3 v = glm::cross(v2, v1);
    float angle = acos(glm::dot(v2, v1) / (glm::length(v2) * glm::length(v1)));
    glm::mat4 rotmat = glm::mat4(1.0);
    if (glm::dot(v2, v1) == 1)
        return rotmat;
    rotmat = glm::rotate(rotmat, angle, v);
    return rotmat;
}

void    Camera::updateCamera()
{
    _dirLook = glm::vec3(sin(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)),
                         sin(glm::radians(_rotateX)),
                         cos(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)));

    _view = glm::lookAt(_cameraPos, _cameraPos + _dirLook, _cameraUp);

    glm::mat4 rot = doRotation(_dirLook, glm::vec3(0, 0, 1));
    glm::vec3 right = rot * glm::vec4(1, 0, 0, 1);
    glm::vec3 up = rot * glm::vec4(_cameraUp, 1);

    float tanFov = tan(_fov / 2);

    float heightNear = (2.f * tanFov * _near) / 2.f;
    float widthNear = (heightNear * _screenRatio) / 2.f;

    float heightFar = (2.f * tanFov * _far) / 2.f;
    float widthFar = (heightFar * _screenRatio) / 2.f;

    glm::vec3 centerNear = _cameraPos + _dirLook * _near;
    glm::vec3 centerFar = _cameraPos + _dirLook * _far;

    auto nearTopLeft = centerNear + _cameraUp * heightNear + right * -widthNear;
    auto nearTopRight = centerNear + _cameraUp * heightNear + right * widthNear;
    auto nearBottomLeft = centerNear + _cameraUp * -heightNear + right * -widthNear;
    auto nearBottomRight = centerNear + _cameraUp * -heightNear + right * widthNear;

    auto farTopLeft = centerFar + _cameraUp * heightFar + right * -widthFar;
    auto farTopRight = centerFar + _cameraUp * heightFar + right * widthFar;
    auto farBottomLeft = centerFar + _cameraUp * -heightFar + right * -widthFar;
    auto farBottomRight = centerFar + _cameraUp * -heightFar + right * widthFar;

    std::cout << "---------" << std::endl;
    std::cout << _dirLook.x << " " << _dirLook.y << " " << _dirLook.z << std::endl;
    std::cout << right.x << " " << right.y << " " << right.z << std::endl;
    std::cout << up.x << " " << up.y << " " << up.z << std::endl;
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
    Window::close();
}

/////////////////////
//
//	MOVE	
//
/////////////////////

void	Camera::moveLeft(float deltaTime)
{
    _cameraPos -= _translationCelerity * deltaTime * glm::normalize(glm::cross(_cameraUp, _dirLook));
}

void	Camera::moveRight(float deltaTime)
{
    _cameraPos += _translationCelerity * deltaTime * glm::normalize(glm::cross(_cameraUp, _dirLook));
}

void	Camera::moveBack(float deltaTime)
{
    _cameraPos -= _translationCelerity * deltaTime * _dirLook;
}

void	Camera::moveForward(float deltaTime)
{
    _cameraPos += _translationCelerity * deltaTime * _dirLook;
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