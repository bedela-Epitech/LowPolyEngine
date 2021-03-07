

#include "encapsulation/Input.h"
#include "encapsulation/Renderer.h"
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
        std::unique_ptr<Terrain> terrain = std::make_unique<Terrain>("../shaders/terrain.vs", "../shaders/terrain.fs");
        terrain->_loadingThread = std::thread(&Terrain::generateTerrain, terrain.get());

        std::unique_ptr<Camera> camera = std::make_unique<Camera>(250.f, 250.0f, -3.f); //eye position
        std::unique_ptr<Menu> menu = std::make_unique<Menu>("../shaders/texture.vs", "../shaders/texture.fs", "../ressources/maxresdefault960x540.jpg", "../ressources/backgroundloading.jpg");
        std::unique_ptr<ShadowMap> shadowMap = std::make_unique<ShadowMap>("../shaders/shadow.vs", "../shaders/shadow.fs", false, true, 2000, 2000);

        Input inputKeys(camera.get(), menu.get());

        Renderer renderer(std::move(terrain), std::move(menu), std::move(shadowMap), std::move(camera));

        while (window.isOpen())
        {
            inputKeys.keyManager();
            inputKeys.mouseManger();

            renderer.updateShader();

            renderer.display();

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