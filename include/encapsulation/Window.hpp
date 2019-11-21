

#ifndef _LEDEB_WINDOW_HPP_
#define _LEDEB_WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <iostream>

class Window
{
public:
    GLFWwindow* _window;
    glm::ivec2   _windowSize;

public:
    Window() = default;
    Window(int, int);
    static void framebufferSizeCallback(GLFWwindow* , int , int );
    void update();
    bool isOpen();
    void close();
};

#endif // !_LEDEB_WINDOW_HPP_
