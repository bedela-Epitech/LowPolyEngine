
#include "encapsulation/L_OpenGL.hpp"

/////////////////////
//
//	INIT
//
/////////////////////


L_OpenGL::L_OpenGL(const std::string &mapVsPath, const std::string &mapFsPath,
                   const std::shared_ptr<Menu> &menu)
        : _menu(menu), _terrain(mapVsPath, mapFsPath)
{
    GLCall(glEnable(GL_DEPTH_TEST));

    _loadingThread = std::thread(&Terrain::generateTerrain, &_terrain);
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
        _menu->_textShader.use();
        if (_terrain._isTerrainReady && !_terrain._isTerrainLinked)
        {
            _loadingThread.join();
            _terrain.bindTerrain();
            _terrain._isTerrainLinked = true;
            _menu->_textShader.use();
        }
    }
    else
    {
        _terrain._shader.use();
        _terrain._shader.setVec3("cameraDir", dirLook);
        _terrain._shader.setMat4("view", view);
    }
}

void    L_OpenGL::display()
{
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    if (!(_menu->_linkDone && _terrain._isTerrainLinked))
    {
        GLCall(glBindVertexArray(_menu->_vArray._vArrayId));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _menu->_vertexNb));
    }
    else
    {
        GLCall(glBindVertexArray(_terrain._vArray._vArrayId));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _terrain._vertexNb));
    }
}