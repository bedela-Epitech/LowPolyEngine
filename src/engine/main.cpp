
//#include <stb_image.h>

#include "encapsulation/Input.hpp"
#include "encapsulation/L_OpenGL.hpp"
#include <iostream>

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);

    window.loadFunctions();

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(0.f, 0.0f, -3.f, // eye position
                                                              0.0f, 1.0f, 0.0f, // eye look at direction
                                                              0.0f, 0.0f, 1.0f); // eye look up direction
    Input inputKeys(camera);

    L_OpenGL opengl("../7.1.camera.vs", "../7.1.camera.fs");

    opengl.linkVertices();
    opengl.linkColors();
    opengl.linkNormals();

    opengl._shader.setMat4("projection", camera->_projection);

    while (window.isOpen())
    {
        inputKeys.KeyManager();

        camera->updateCamera();

        opengl._shader.use();
        opengl._shader.setVec3("cameraDir", camera->_dirLook);
        opengl._shader.setMat4("view", camera->_view);

        opengl.display();

        window.update();
    }

    opengl.cleanUp();

    window.close();

    return 0;
}

