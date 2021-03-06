
#include "encapsulation/L_OpenGL.h"

/////////////////////
//
//	INIT
//
/////////////////////

L_OpenGL::L_OpenGL(const std::shared_ptr<Terrain> &terrain, const std::shared_ptr<Menu> &menu, const std::shared_ptr<ShadowMap> &shadowMap)
        : _terrain(terrain), _menu(menu), _shadowMap(shadowMap)
{
    _light = std::make_unique<Light>();
    GLCall(glEnable(GL_DEPTH_TEST));
}

void    L_OpenGL::initShader(const glm::mat4 &projection)
{
    _terrain->_projection = projection;
}

void    L_OpenGL::updateShader(std::shared_ptr<Camera> camera)
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
        _light->updateLight(camera);
        _shadowMap->updateShader(_light->_mvp);
        _terrain->updateShader(camera, _light->getBiasLightMvp(), _shadowMap->_fbo._depthTexture._textureId);
    }
}

void    L_OpenGL::clear() const
{
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void    L_OpenGL::display() const
{
    clear();

    if (!(_menu->_linkDone && _terrain->_isTerrainLinked))
    {
        _menu->_gui.draw();
    }
    else
    {
        _shadowMap->draw();
        Texture::unbind();
        _terrain->_shader.use();
        _shadowMap->_fbo._depthTexture.bind();
        _terrain->draw();
    }
}