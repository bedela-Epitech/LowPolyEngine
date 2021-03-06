

#include "encapsulation/Input.h"
#include "encapsulation/L_OpenGL.h"
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

        std::shared_ptr<Camera> camera = std::make_shared<Camera>(250.f, 250.0f, -3.f); //eye position
        std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>("../shaders/terrain.vs", "../shaders/terrain.fs");
        terrain->_loadingThread = std::thread(&Terrain::generateTerrain, terrain);
        std::shared_ptr<Menu> menu = std::make_shared<Menu>("../shaders/texture.vs", "../shaders/texture.fs", "../ressources/maxresdefault960x540.jpg", "../ressources/backgroundloading.jpg");
        std::shared_ptr<ShadowMap> shadowMap = std::make_shared<ShadowMap>("../shaders/shadow.vs", "../shaders/shadow.fs", terrain, false, true, 2000, 2000);
        Input inputKeys(camera, menu);


        L_OpenGL opengl(terrain, menu, shadowMap);


        opengl.initShader(camera->_projection);

        while (window.isOpen()) {
            inputKeys.keyManager();
            inputKeys.mouseManger();

            camera->updateCamera();
            opengl.updateShader(camera);

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