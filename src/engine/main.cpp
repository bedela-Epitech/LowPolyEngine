

#include "encapsulation/Input.h"
#include "encapsulation/L_OpenGL.h"
#include "encapsulation/Texture.h"
#include <iostream>
#include <exception>

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, false);
    try
    {
        window.loadFunctions();

        std::shared_ptr<Camera> camera = std::make_shared<Camera>(1000.f, 1000.0f, -3.f, // eye position
                                                                  0.0f, 1.0f, 0.0f, // eye look at direction
                                                                  0.0f, 0.0f, 1.0f); // eye look up direction
        std::shared_ptr<Menu> menu = std::make_shared<Menu>("../shaders/texture.vs", "../shaders/texture.fs",
                                                            "../ressources/maxresdefault960x540.jpg",
                                                            "../ressources/backgroundloading.jpg");
        Input inputKeys(camera, menu);


        L_OpenGL opengl("../shaders/terrain.vs", "../shaders/terrain.fs", menu);


        opengl.initShader(camera->_projection);

        while (window.isOpen()) {
            inputKeys.keyManager();
            inputKeys.mouseManger();

            camera->updateCamera();

            opengl.updateShader(camera->_dirLook, camera->_view);

            opengl.display();

            window.update();
        }
    }
    catch (const std::exception &error)
    {
        std::cout << "Error : " << error.what() << std::endl;
    }
    Window::terminate();

    return 0;
}