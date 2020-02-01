
//#include <stb_image.h>

#include "encapsulation/Input.hpp"
#include "encapsulation/L_OpenGL.hpp"
#include "encapsulation/Texture.h"
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

    L_OpenGL opengl("../terrain.vs", "../terrain.fs",
                    "../texture.vs", "../texture.fs");

    Texture texture("../ressources/background.jpg");
    texture.bind();

    opengl.setTexture(0); // textureID

    opengl.linkTerrainInfo();

    opengl.initShader(camera->_projection);

    while (window.isOpen())
    {
        inputKeys.KeyManager();

        camera->updateCamera();

        opengl.updateShader(camera->_dirLook, camera->_view);

        opengl.display();

        window.update();
    }

    opengl.cleanUp();

    window.close();

    return 0;
}

