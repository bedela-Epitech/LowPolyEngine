//
// Created by adrien on 03/01/20.
//

#include "map/Terrain.h"

// Path to Vertex Shader and Fragment Shader
Terrain::Terrain(const std::string &vsPath, const std::string &fsPath)
: _shader(vsPath, fsPath), _bufferLayout(_shader.ID)
{
    QuadTree qt(9);
    qt.addEastChunk();
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

    _bufferLayout.addElement<float>("aPos", 3, GL_FALSE);
    _bufferLayout.addElement<float>("in_Color", 3, GL_FALSE);
    _bufferLayout.addElement<float>("normal", 3, GL_FALSE);
}

void Terrain::bindTerrain()
{

}