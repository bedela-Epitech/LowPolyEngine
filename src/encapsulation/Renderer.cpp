//
// Created by adrien on 15/11/19.
//

#include "encapsulation/Renderer.h"

/////////////////////
//
//	INIT
//
/////////////////////

Renderer::Renderer(std::unique_ptr<Terrain> terrain, std::unique_ptr<Menu> menu, std::unique_ptr<ShadowMap> shadowMap, std::unique_ptr<Camera> camera)
        : _terrain(std::move(terrain)), _menu(std::move(menu)), _shadowMap(std::move(shadowMap)), _camera(std::move(camera))
{
    _light = std::make_unique<Light>();
    GLCall(glEnable(GL_DEPTH_TEST));
}

void    Renderer::updateShader()
{
    if (!(_menu->_linkDone && _terrain->_isTerrainLinked))
    {
        _menu->useShader();
        if (_terrain->_isTerrainReady && !_terrain->_isTerrainLinked)
        {
            _terrain->_loadingThread.join();
            _terrain->bindTerrain(_light);
            _terrain->_isTerrainLinked = true;
            _menu->useShader();
        }
    }
    else
    {
        _camera->updateCamera();
        _light->updateLight(_camera);

        _shadowMap->updateShader(_light->_mvp);
        _terrain->updateShader(_camera, _light->getBiasLightMvp(), _shadowMap->_fbo._depthTexture._textureId);
    }
}

void    Renderer::clear() const
{
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void    Renderer::display() const
{
    clear();

    if (!(_menu->_linkDone && _terrain->_isTerrainLinked))
    {
        _menu->_gui.draw();
    }
    else
    {
        _shadowMap->draw(_terrain);
        Texture::unbind();
        _terrain->_shader.use();
        _shadowMap->_fbo._depthTexture.bind();
        _terrain->draw();
    }
}