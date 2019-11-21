
//#include <stb_image.h>

#include "encapsulation/Input.hpp"
#include "encapsulation/L_OpenGL.hpp"
#include <iostream>

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------


    L_OpenGL opengl("../7.1.camera.vs", "../7.1.camera.fs");
    // build and compile our shader zprogram
    // ------------------------------------

    opengl.linkVertices();
    opengl.linkColors();
    opengl.linkNormals();

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    opengl._shader.setMat4("projection", glm::perspective(60.f, (float)window._windowSize.x / (float)window._windowSize.y, 0.1f, 2200.f));

    Camera *camera = new Camera(window._windowSize,
                                0.f, 0.0f, -3.f, // eye position
                                0.0f, 1.0f, 0.0f, // eye look at direction
                                0.0f, 0.0f, 1.0f); // eye look up direction
    Input inputKeys(camera, window._window);
    // render loop
    // -----------
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

