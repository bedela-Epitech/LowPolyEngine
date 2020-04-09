//
// Created by adrien on 21/11/19.
//

#include "encapsulation/Window.h"

// Declare static members
GLFWwindow * Window::_window;
glm::ivec2   Window::_windowSize;

Window::Window(int sizeX, int sizeY, bool fullScreen)
{
    _windowSize = glm::ivec2(sizeX, sizeY);

    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // active cursor

    // glfw window creation
    // --------------------
    if (fullScreen)
        _window = glfwCreateWindow(_windowSize.x, _windowSize.y, "LowPolyEngine", glfwGetPrimaryMonitor(), NULL);
    else
        _window = glfwCreateWindow(_windowSize.x, _windowSize.y, "LowPolyEngine", NULL, NULL);


    if (_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

float   Window::getScreenRatio()
{
    return (static_cast<float>(_windowSize.x) / static_cast<float>(_windowSize.y));
}

bool    Window::isOpen()
{
    return(!(bool)glfwWindowShouldClose(_window));
}

void    Window::close()
{
    glfwSetWindowShouldClose(_window, true);
}

void    Window::terminate()
{
    glfwTerminate();
}

void    Window::update()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

double  Window::getTime()
{
    return (glfwGetTime());
}

int     Window::getKey(int key)
{
    return (glfwGetKey(_window, key));
}

void    Window::hideCursor()
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

int     Window::getMouseClick(int key)
{
    return (glfwGetMouseButton(_window, key));
}

glm::dvec2 Window::getCursorPos()
{
    glm::dvec2 pos;
    glfwGetCursorPos(_window, &pos.x, &pos.y);
    return pos;
}

void    Window::loadFunctions()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}
