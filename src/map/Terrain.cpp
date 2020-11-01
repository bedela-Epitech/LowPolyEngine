//
// Created by adrien on 03/01/20.
//

#include "map/Terrain.h"

// Path to Vertex Shader and Fragment Shader
Terrain::Terrain(const std::string &vsPath, const std::string &fsPath)
        : _shader(vsPath, fsPath), _bufferLayout(_shader.ID)
{
    _shader.use();

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
    QuadTree qt(6);
    qt.addChunk(glm::ivec2(1, 0));
    qt.addChunk(glm::ivec2(0, 1));
    qt.addChunk(glm::ivec2(-1, 0));
    qt.addChunk(glm::ivec2(-1, 0));
    qt.addChunk(glm::ivec2(0, -1));
    qt.addChunk(glm::ivec2(0, -1));
    qt.addChunk(glm::ivec2(1, 0));
    qt.addChunk(glm::ivec2(1, 0));
    qt.addChunk(glm::ivec2(1, 0));
    qt.addChunk(glm::ivec2(0, 1));
    qt.addChunk(glm::ivec2(0, 1));
    qt.addChunk(glm::ivec2(0, 1));
    qt.addChunk(glm::ivec2(-1, 0));
    qt.addChunk(glm::ivec2(-1, 0));
    qt.addChunk(glm::ivec2(-1, 0));
    qt.addChunk(glm::ivec2(-1, 0));
    qt.addChunk(glm::ivec2(0, -1));
    qt.addChunk(glm::ivec2(0, -1));
    qt.addChunk(glm::ivec2(0, -1));
    qt.addChunk(glm::ivec2(1, 0));
    qt.addChunk(glm::ivec2(1, 0));
    qt.addChunk(glm::ivec2(1, 0));
    qt.gatherChunks();

    for (int i = 0; i < qt._vertices.size(); i++)
    {
        _vertices.push_back(qt._vertices[i].x);
        _vertices.push_back(qt._vertices[i].y);
        _vertices.push_back(qt._vertices[i].z);


        _vertices.push_back(qt._normals[i / 3].x);
        _vertices.push_back(qt._normals[i / 3].y);
        _vertices.push_back(qt._normals[i / 3].z);


        _vertices.push_back(qt._colors[i].x);
        _vertices.push_back(qt._colors[i].y);
        _vertices.push_back(qt._colors[i].z);

    }
    _vertices.push_back(50.f);
    _vertices.push_back(100.f);
    _vertices.push_back(50.f);

    _vertices.push_back(0.f);
    _vertices.push_back(0.f);
    _vertices.push_back(-1.f);

    _vertices.push_back(1.f);
    _vertices.push_back(0.f);
    _vertices.push_back(0.f);

    _vertices.push_back(-50.f);
    _vertices.push_back(100.f);
    _vertices.push_back(50.f);

    _vertices.push_back(0.f);
    _vertices.push_back(0.f);
    _vertices.push_back(-1.f);

    _vertices.push_back(1.f);
    _vertices.push_back(0.f);
    _vertices.push_back(0.f);

    _vertices.push_back(50.f);
    _vertices.push_back(150.f);
    _vertices.push_back(50.f);

    _vertices.push_back(0.f);
    _vertices.push_back(0.f);
    _vertices.push_back(-1.f);

    _vertices.push_back(1.f);
    _vertices.push_back(0.f);
    _vertices.push_back(0.f);

    _vertexNb = _vertices.size() / 3;

    _isTerrainReady = true;
}

void Terrain::bindTerrain()
{
    _shader.use();

    _shader.setVec3("lightDir", _sun._lightDir);
    _shader.setFloat("ambiantCoeff", _sun._ambiantCoeff);
    _shader.setVec3("lightColor", _sun._lightColor);
    _shader.setFloat("specularStrength", _sun._specularStrenght);

    _vArray.addVertexBuffer(_vertices.data(), sizeof(float) * _vertices.size(), _bufferLayout);
}

void    Terrain::draw() const
{
    GLCall(glBindVertexArray(_vArray._vArrayId));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, _vertexNb));
}

//////////////////
//
//      SUN
//
//////////////////

void Terrain::setDir(const glm::vec3 &dir)
{
    _sun.setDir(dir);
    _shader.setVec3("lightDir", _sun._lightDir);
}

void Terrain::setColor(const glm::vec3 &color)
{
    _sun.setColor(color);
    _shader.setVec3("lightColor", _sun._lightColor);
}

void Terrain::setAmbient(float ambiant)
{
    _sun.setAmbient(ambiant);
    _shader.setFloat("ambiantCoeff", _sun._ambiantCoeff);
}

void Terrain::setSpecular(float specular)
{
    _sun.setSpecular(specular);
    _shader.setFloat("specularStrength", _sun._specularStrenght);
}