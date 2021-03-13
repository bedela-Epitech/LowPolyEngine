//
// Created by adrien on 03/01/20.
//

#include "map/Terrain.h"

// Path to Vertex Shader and Fragment Shader
Terrain::Terrain(const std::string &vsPath, const std::string &fsPath)
        : _shader(vsPath, fsPath), _bufferLayout(_shader.ID), _qt((unsigned int)pow(2, 6) + 1)
{
    _qt.addChunk(glm::ivec2(1, 0));
    _qt.addChunk(glm::ivec2(1, 1));
    _qt.addChunk(glm::ivec2(-1, 0));
    _qt.addChunk(glm::ivec2(-1, -1));
    _qt.addChunk(glm::ivec2(0, -1));
    _qt.addChunk(glm::ivec2(0, 1));
    _qt.addChunk(glm::ivec2(1, -1));
    _qt.addChunk(glm::ivec2(-1, 1));

    _shader.use();
    _size = (unsigned int)pow(2, 6) + 1;

    try {
        _bufferLayout.addElement<float>("aPos", 3, GL_FALSE);
        _bufferLayout.addElement<float>("normal", 3, GL_FALSE);
        _bufferLayout.addElement<float>("in_Color", 3, GL_FALSE);
    }
    catch (const std::invalid_argument &error) {
        throw std::invalid_argument("in Terrain, invalid shader variable name");
    }
}

void Terrain::generateTerrain()
{
    _vertices.clear();
    _qt.gatherChunks();

    for (int i = 0; i < _qt._vertices.size(); i++)
    {
        _vertices.push_back(_qt._vertices[i].x);
        _vertices.push_back(_qt._vertices[i].y);
        _vertices.push_back(_qt._vertices[i].z);


        _vertices.push_back(_qt._normals[i / 3].x);
        _vertices.push_back(_qt._normals[i / 3].y);
        _vertices.push_back(_qt._normals[i / 3].z);


        _vertices.push_back(_qt._colors[i].x);
        _vertices.push_back(_qt._colors[i].y);
        _vertices.push_back(_qt._colors[i].z);

    }
    auto c = ModelCreator::getCube(glm::vec3(0.f, 100.f, 0.f),  50.f);
    _vertices.insert(_vertices.end(), c.begin(), c.end());

    _vertexNb = _vertices.size() / 3;

    _isTerrainReady = true;
}

void Terrain::bindTerrain(const std::unique_ptr<Light> &light)
{
    _shader.use();

    _shader.setVec3("lightDir", light->_lightDir);
    _shader.setFloat("ambiantCoeff", light->_ambiantCoeff);
    _shader.setVec3("lightColor", light->_lightColor);
    _shader.setFloat("specularStrength", light->_specularStrenght);

    _vArray.addVertexBuffer(_vertices.data(), sizeof(float) * _vertices.size(), _bufferLayout);
}

void Terrain::update(const std::unique_ptr<Camera> &camera, const glm::mat4 &BiaslightMvp, unsigned int shadowMapTextureId)
{
    updatePos(camera->_cameraPos);

    _shader.use();
    _mvp = camera->_projection * camera->_view;
    _shader.setMat4("lightMvp", BiaslightMvp); // toremove
    _shader.setVec3("cameraDir", camera->_cameraLook);
    _shader.setMat4("mvp", _mvp);
    _shader.setInt("shadowMap", shadowMapTextureId);
}

void Terrain::updatePos(const glm::vec3 &cameraPos)
{
    // know in which chunk we are
    int xFind = (int)(cameraPos.x / 8.f) / (int)_size;
    int zFind = (int)(cameraPos.z / 8.f) / (int)_size;
    // if a chunk is size 10 and the xPosition is 5 :
    // 5 / 10 = 0, chunk X position is 0
    // but -5 /10 = 0, which is false, we are actually
    // in the chunk X position -1. So we decrement to patch this
    xFind -= (cameraPos.x < 0);
    zFind -= (cameraPos.z < 0);

    if (_qt._miniMap.find({xFind, zFind}) == _qt._miniMap.end())
    {
        _qt.addChunk({xFind, zFind});
        generateTerrain();
        modifyTerrain();
    }
    std::cout << "pos = " << xFind << " " << zFind << std::endl;
    // get the chunk with the help of its position
    /*auto [pos, quad] = *_miniMap.find({xFind, zFind});
    auto [xPos, zPos] = pos;
    // shift the absolute position to the map position
    xPos  = x[j] - (int)_size * xPos;
    zPos = z[j] - (int)_size * zPos;*/
}

void Terrain::modifyTerrain()
{
    _vArray.modifyData(_vertices.data(), sizeof(float) * _vertices.size());
}

void    Terrain::draw() const
{
    GLCall(glBindVertexArray(_vArray._vArrayId));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, _vertexNb));
}