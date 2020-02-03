
#include "encapsulation/L_OpenGL.hpp"

/////////////////////
//
//	INIT
//
/////////////////////

L_OpenGL::L_OpenGL(const std::string &mapVsPath, const std::string &mapFsPath,
                   const std::string &textVsPath, const std::string &textFsPath)
        : _mapShader(mapVsPath, mapFsPath), _textShader(textVsPath, textFsPath),
          _loadingThread(&L_OpenGL::generateTerrain, this)
{
    glEnable(GL_DEPTH_TEST);

    initTexture();
}

void    L_OpenGL::initTexture()
{
    _textVertices = {
            -1.f, -1.f, 0.f, 0.f,
            1.f, -1.f, 1.f, 0.f,
            1.f, 1.f, 1.f, 1.f,

            -1.f, 1.f, 0.f, 1.f,
            -1.f, -1.f, 0.f, 0.f,
            1.f, 1.f, 1.f, 1.f,
    };
    linkTextureInfo();
}

void    L_OpenGL::generateTerrain()
{
    QuadTree qt(9);
    qt.addEastChunk();
    qt.gatherChunks();

    for (int i = 0; i < qt._vertices.size(); i++)
    {
        _mapVertices.push_back(qt._vertices[i].x);
        _mapVertices.push_back(qt._vertices[i].y);
        _mapVertices.push_back(qt._vertices[i].z);

        _mapVertices.push_back(qt._normals[i / 3].x);
        _mapVertices.push_back(qt._normals[i / 3].y);
        _mapVertices.push_back(qt._normals[i / 3].z);

        _mapVertices.push_back(qt._colors[i].x);
        _mapVertices.push_back(qt._colors[i].y);
        _mapVertices.push_back(qt._colors[i].z);
    }

    _isMapReady = true;
}

void    L_OpenGL::initShader(const glm::mat4 &projection)
{
    _mapShader.use();
    _mapShader.setMat4("projection", projection);

}

void    L_OpenGL::updateShader(const glm::vec3 &dirLook, const glm::mat4 &view)
{
    if (_linkDone == false)
    {
        _textShader.use();
        if (_isMapReady)
        {
            _loadingThread.join();
            std::cout << _mapVertices.size() << std::endl;
            _mapShader.use();

            _mapShader.setVec3("lightDir", _light._lightDir);
            _mapShader.setFloat("ambiantCoeff", _light._ambiantCoeff);
            _mapShader.setVec3("lightColor", _light._lightColor);
            _mapShader.setFloat("specularStrength", _light._specularStrenght);
            linkTerrainInfo();
            _linkDone = true;
        }
    }
    else
    {
        _mapShader.use();
        _mapShader.setVec3("cameraDir", dirLook);
        _mapShader.setMat4("view", view);
    }
}

void    L_OpenGL::linkTextureInfo()
{
    int vpos_location = glGetAttribLocation(_textShader.ID, "aPos");
    auto vtext_location = glGetAttribLocation(_textShader.ID, "textCoord");

    glGenVertexArrays(1, &_textVAO);
    glGenBuffers(1, &_textVBO);

    glBindVertexArray(_textVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _textVAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _textVertices.size(), _textVertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
    glEnableVertexAttribArray(vpos_location);

    glVertexAttribPointer(vtext_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *)(sizeof(float) * 2));
    glEnableVertexAttribArray(vtext_location);
}

void    L_OpenGL::linkTerrainInfo()
{
    int vpos_location = glGetAttribLocation(_mapShader.ID, "aPos");
    auto vcol_location = glGetAttribLocation(_mapShader.ID, "in_Color");
    auto vnorm_location = glGetAttribLocation(_mapShader.ID, "normal");

    glGenVertexArrays(1, &_mapVAO);
    glGenBuffers(1, &_mapVBO);

    glBindVertexArray(_mapVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _mapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _mapVertices.size(), _mapVertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, nullptr);
    glEnableVertexAttribArray(vpos_location);

    glVertexAttribPointer(vnorm_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(vnorm_location);

    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (const void *)(sizeof(float) * 6));
    glEnableVertexAttribArray(vcol_location);
}

void    L_OpenGL::setTexture(int textureID)
{
    _textShader.setInt("u_Texture", textureID);
}

void    L_OpenGL::display()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (_linkDone == false)
    {
        glBindVertexArray(_textVAO);
        glDrawArrays(GL_TRIANGLES, 0, _textVertices.size() / 3);
    }
    else if (_linkDone == true)
    {
        glBindVertexArray(_mapVAO);
        glDrawArrays(GL_TRIANGLES, 0, _mapVertices.size() / 3);
    }
}

void    L_OpenGL::cleanUp()
{
    glDeleteVertexArrays(1, &_mapVAO);
    glDeleteBuffers(1, &_mapVBO);
}

void L_OpenGL::setDir(const glm::vec3 &dir)
{
    _light.setDir(dir);
    _mapShader.setVec3("lightDir", _light._lightDir);
}

void L_OpenGL::setColor(const glm::vec3 &color)
{
    _light.setColor(color);
    _mapShader.setVec3("lightColor", _light._lightColor);
}

void L_OpenGL::setAmbient(float ambiant)
{
    _light.setAmbient(ambiant);
    _mapShader.setFloat("ambiantCoeff", _light._ambiantCoeff);
}

void L_OpenGL::setSpecular(float specular)
{
    _light.setSpecular(specular);
    _mapShader.setFloat("specularStrength", _light._specularStrenght);
}