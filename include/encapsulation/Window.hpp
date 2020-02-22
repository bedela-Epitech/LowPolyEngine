

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
    static glm::ivec2   _windowSize;

public:
    Window() = delete;
    Window(int, int, bool);

    void update();
    bool isOpen();
    void loadFunctions();

    static void close();
    static void hideCursor();
    static glm::dvec2 getCursorPos();
    static double getTime();
    static int getKey(int);
    static int getMouseClick(int);
    static float getScreenRatio();
};

#endif // !_LEDEB_WINDOW_HPP_
