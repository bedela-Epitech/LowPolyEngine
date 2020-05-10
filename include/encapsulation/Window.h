//
// Created by adrien on 03/01/20.
//

#ifndef _LEDEB_WINDOW_H_
#define _LEDEB_WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>
#include <memory>

class Window
{
public:
    inline static GLFWwindow   *_window;
    inline static glm::ivec2   _windowSize;

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
    static void terminate();
};

#endif // !_LEDEB_WINDOW_H_
