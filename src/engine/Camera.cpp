
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
    _far = 10040.f;
    _projection = glm::perspective(glm::radians(_fov), _screenRatio, _near, _far);
    _projection = glm::scale(_projection, glm::vec3(-1, 1, 1));

    _corners = std::vector<glm::vec3>(8);
}

/////////////////////
//
//	CAMERA
//
/////////////////////

glm::mat4    doRotation(glm::vec3 v1, glm::vec3 v2)
{
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

double getDist(glm::vec3 a, glm::vec3 b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

void    Camera::updateCamera()
{
    _dirLook = glm::vec3(sin(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)),
                         sin(glm::radians(_rotateX)),
                         cos(glm::radians(_rotateY)) * cos(glm::radians(_rotateX)));
    glm::vec3 upp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(upp, _dirLook));
    _cameraUp = glm::cross(_dirLook, cameraRight);


    _view = glm::lookAt(_cameraPos, _cameraPos + _dirLook, _cameraUp);

    glm::mat4 rot = doRotation(_dirLook, glm::vec3(0, 0, 1));

    float tanFov = tanf((_fov / 2.f) * M_PI / 180.0 );

    float heightNear = (2.f * tanFov * _near) / 2.f;
    float widthNear = (heightNear * _screenRatio) / 2.f;

    float heightFar = (2.f * tanFov * (_far / 10.f)) / 2.f;
    float widthFar = (heightFar * _screenRatio) / 2.f;

    glm::vec3 centerNear = _cameraPos + _dirLook * _near;
    glm::vec3 centerFar = _cameraPos + _dirLook * (_far / 10.f);

    std::cout << "camera Look" << _dirLook.x << " " << _dirLook.y << " " << _dirLook.z << std::endl;
    std::cout << "camera up" << _cameraUp.x << " " << _cameraUp.y << " " << _cameraUp.z << std::endl;


    /*std::cout << "centerNear" << centerNear.x << " " << centerNear.y << " " << centerNear.z << std::endl;
    std::cout << "centerFar" << centerFar.x << " " << centerFar.y << " " << centerFar.z << std::endl;
    std::cout << "dist = " << getDist(centerNear, centerFar) << std::endl;
    std::cout << "HN = " << heightNear << std::endl;
    std::cout << "HF = " << tanFov << std::endl;*/

    auto nearTopLeft = centerNear + _cameraUp * heightNear + cameraRight * -widthNear;
    auto nearTopRight = centerNear + _cameraUp * heightNear + cameraRight * widthNear;
    auto nearBottomLeft = centerNear + _cameraUp * -heightNear + cameraRight * -widthNear;
    auto nearBottomRight = centerNear + _cameraUp * -heightNear + cameraRight * widthNear;

    auto farTopLeft = centerFar + _cameraUp * heightFar + cameraRight * -widthFar;
    auto farTopRight = centerFar + _cameraUp * heightFar + cameraRight * widthFar;
    auto farBottomLeft = centerFar + _cameraUp * -heightFar + cameraRight * -widthFar;
    auto farBottomRight = centerFar + _cameraUp * -heightFar + cameraRight * widthFar;


    _corners[0] = glm::vec3(0, 0, 0);
    _corners[1] = glm::vec3(0, 0, 0);
    _corners[2] = glm::vec3(0, 0, 0);
    _corners[3] = glm::vec3(0, 0, 0);
    /*_corners[0] = nearTopLeft;
    _corners[1] = nearTopRight;
    _corners[2] = nearBottomLeft;
    _corners[3] = nearBottomRight;*/

    _corners[4] = farTopLeft;
    _corners[5] = farTopRight;
    _corners[6] = farBottomLeft;
    _corners[7] = farBottomRight;

    /*std::cout << "nearTopLeft = " << nearTopLeft.x << " " << nearTopLeft.y << " " << nearTopLeft.z << std::endl;
    std::cout << "nearTopRight = " << nearTopRight.x << " " << nearTopRight.y << " " << nearTopRight.z << std::endl;
    std::cout << "nearBottomLeft = " << nearBottomLeft.x << " " << nearBottomLeft.y << " " << nearBottomLeft.z << std::endl;
    std::cout << "nearBottomRight = " << nearBottomRight.x << " " << nearBottomRight.y << " " << nearBottomRight.z << std::endl;

    std::cout << "farTopLeft = " << farTopLeft.x << " " << farTopLeft.y << " " << farTopLeft.z << std::endl;
    std::cout << "farTopRight = " << farTopRight.x << " " << farTopRight.y << " " << farTopRight.z << std::endl;
    std::cout << "farBottomLeft = " << farBottomLeft.x << " " << farBottomLeft.y << " " << farBottomLeft.z << std::endl;
    std::cout << "farBottomRight = " << farBottomRight.x << " " << farBottomRight.y << " " << farBottomRight.z << std::endl;*/

    glm::vec3 sun(-1, -1, 0);
    glm::mat4 rotSun = doRotation(sun, glm::vec3(0, 0, 1));
    auto upSun = rotSun * glm::vec4(0, 1, 0, 1);
    _upSun = upSun;
    glm::vec3 array[8];

    array[0] = rotSun * glm::vec4(nearTopLeft, 1.0);
    array[1] = rotSun * glm::vec4(nearTopRight, 1.0);
    array[2] = rotSun * glm::vec4(nearBottomLeft, 1.0);
    array[3] = rotSun * glm::vec4(nearBottomRight, 1.0);

    array[4] = rotSun * glm::vec4(farTopLeft, 1.0);
    array[5] = rotSun * glm::vec4(farTopRight, 1.0);
    array[6] = rotSun * glm::vec4(farBottomLeft, 1.0);
    array[7] = rotSun * glm::vec4(farBottomRight, 1.0);

    /*std::cout << array[0].x << " " << array[0].y << " " << array[0].z << std::endl;
    std::cout << array[1].x << " " << array[1].y << " " << array[1].z << std::endl;
    std::cout << array[2].x << " " << array[2].y << " " << array[2].z << std::endl;
    std::cout << array[3].x << " " << array[3].y << " " << array[3].z << std::endl;
    std::cout << array[4].x << " " << array[4].y << " " << array[4].z << std::endl;
    std::cout << array[5].x << " " << array[5].y << " " << array[5].z << std::endl;
    std::cout << array[6].x << " " << array[6].y << " " << array[6].z << std::endl;
    std::cout << array[7].x << " " << array[7].y << " " << array[7].z << std::endl;*/

    float minX = array[0].x;
    float minY = array[0].y;
    float minZ = array[0].z;
    float maxX = array[0].x;
    float maxY = array[0].y;
    float maxZ = array[0].z;
    glm::vec3 centroid(0, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        minX = std::min(minX, array[i].x);
        minY = std::min(minY, array[i].y);
        minZ = std::min(minZ, array[i].z);
        maxX = std::max(maxX, array[i].x);
        maxY = std::max(maxY, array[i].y);
        maxZ = std::max(maxZ, array[i].z);
    }
    glm::mat4 rotBackSun = doRotation(glm::vec3(0, 0, 1), sun);
    centroid.x = (maxX + minX) / 2.f;
    centroid.y = (maxY + minY) / 2.f;
    centroid.z = (maxZ + minZ) / 2.f;
    _centroid = rotBackSun * glm::vec4(centroid, 1.0);
    _width = maxX - minX;
    _height = maxY - minY;
    _deep = maxZ - minZ;
    //std::cout << "centroid " << _centroid.x << " " << _centroid.y << " " << _centroid.z << std::endl;


    glm::mat4 actualRot = doRotation(sun, _dirLook);
    glm::mat4 trans = glm::translate(rotSun, _centroid);
    glm::mat4 final = trans;
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(_width * -0.5f, _width * 0.5f,
                                                        _height * -0.5f, _height * 0.5f,
                                                        _deep * -0.5f, _deep * 0.5f);

    glm::mat4 ortho{2.f /_width, 0,             0,           0,
                    0,           2.f / _height, 0,           0,
                    0,           0,             2.f / _deep, 0,
                    0,           0,             0,           1};
    _fff =  glm::mat4(1.0f) * ortho * trans;
    //std::cout << "w = " << _width << ", h " << _height << ", d" << _deep << std::endl;
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