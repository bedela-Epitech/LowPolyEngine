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

    auto cube = getCube(glm::vec3(0.f, 100.f, 0.f),  50.f);
    _vertices.insert(_vertices.end(), cube.begin(), cube.end());

    _vertexNb = _vertices.size() / 3;

    _isTerrainReady = true;
}

std::vector<float> Terrain::getTriangle(const std::vector<glm::vec3> &triPos, const glm::vec3 &normal, const glm::vec3 &color)
{
    std::vector<float> triangle;

    for (const auto &pos : triPos)
    {
        triangle.push_back(pos.x);
        triangle.push_back(pos.y);
        triangle.push_back(pos.z);

        triangle.push_back(normal.x);
        triangle.push_back(normal.y);
        triangle.push_back(normal.z);

        triangle.push_back(color.x);
        triangle.push_back(color.y);
        triangle.push_back(color.z);
    }

    return triangle;
}

std::vector<float> Terrain::getCube(const glm::vec3 &pos, float size)
{
    std::vector<float> cube;
    auto a = getTriangle({pos + glm::vec3(size, -size, -size), pos + glm::vec3(-size, -size, -size), pos + glm::vec3(size, size, -size)} , glm::vec3(0.f, 0.f, -1.f), glm::vec3(1.f, 0.f, 0.f));
    cube.insert(cube.end(), a.begin(), a.end());
    a = getTriangle({pos + glm::vec3(size, size, -size), pos + glm::vec3(-size, -size, -size), pos + glm::vec3(-size, size, -size)} , glm::vec3(0.f, 0.f, -1.f), glm::vec3(1.f, 0.f, 0.f));
    cube.insert(cube.end(), a.begin(), a.end());

    return cube;
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

void Terrain::modifyTerrain()
{
    //_vertices[_vertices.size() - 9] += 1.f;
    _vArray.modifyData(_vertices.data(), sizeof(float) * _vertices.size());
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