//
// Created by adrien on 21/11/19.
//

#include "encapsulation/Window.hpp"

// Declare static members
GLFWwindow * Window::_window;
glm::ivec2   Window::_windowSize;

Window::Window(int sizeX, int sizeY)
{
    _windowSize = glm::ivec2(sizeX, sizeY);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    _window = glfwCreateWindow(_windowSize.x, _windowSize.y, "LearnOpenGL", NULL, NULL);
    if (_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);

}

float   Window::getScreenRatio()
{
    return ((float)(_windowSize.x) / (float)(_windowSize.y));
}

bool    Window::isOpen()
{
    return(!(bool)glfwWindowShouldClose(_window));
}

void    Window::close()
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

void    Window::loadFunctions()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}