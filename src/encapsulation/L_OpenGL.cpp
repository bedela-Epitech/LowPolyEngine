
#include "encapsulation/L_OpenGL.h"

/////////////////////
//
//	INIT
//
/////////////////////

L_OpenGL::L_OpenGL(const std::string &mapVsPath, const std::string &mapFsPath,
                   const std::shared_ptr<Menu> &menu, GUI &gui)
        : _menu(menu), _terrain(mapVsPath, mapFsPath),
          _fbo(true, true, 200, 200), _gui(gui)
{
    GLCall(glEnable(GL_DEPTH_TEST));
    _loadingThread = std::thread(&Terrain::generateTerrain, &_terrain);
    _gui.attachTexture(_fbo._imageTexture);
}

void    L_OpenGL::initShader(const glm::mat4 &projection)
{
    _terrain._shader.use();
    _terrain._shader.setMat4("projection", projection);
}

void    L_OpenGL::updateShader(const glm::vec3 &dirLook, const glm::mat4 &view)
{
    if (!(_menu->_linkDone && _terrain._isTerrainLinked))
    {
        _menu->useShader();
        if (_terrain._isTerrainReady && !_terrain._isTerrainLinked)
        {
            _loadingThread.join();
            _terrain.bindTerrain();
            _terrain._isTerrainLinked = true;
            _menu->useShader();
        }
    }
    else
    {
        _terrain._shader.use();
        _terrain._shader.setVec3("cameraDir", dirLook);
        _terrain._shader.setMat4("view", view);
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

    if (!(_menu->_linkDone && _terrain._isTerrainLinked))
    {
        _menu->_gui.draw();
    }
    else
    {
        _terrain._shader.use();
        _terrain.draw();

        _fbo.bind();
        clear();
        _terrain.draw();
        _fbo.unbind();

        _gui._textShader.use();
        _fbo._imageTexture.bind();
        _gui.draw();
    }
}