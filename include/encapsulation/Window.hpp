

#ifndef _LEDEB_WINDOW_HPP_
#define _LEDEB_WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>
#include <memory>

class Window
{
public:
    static GLFWwindow   *_window;
    inline static GLFWcursor   *_cursor = nullptr;
    static glm::ivec2   _windowSize;
    inline static int                 _width;
    inline static int                 _height;

private:
    static void mouseButtonCallback(GLFWwindow* , int , int , int );

public:
    Window() = delete;
    Window(int, int, bool);

    void update();
    bool isOpen();
    void close();
    void loadFunctions();

    static double getTime();
    static int getKey(int);
    static int getMouseClick(int);
    static float getScreenRatio();
};

#endif // !_LEDEB_WINDOW_HPP_
