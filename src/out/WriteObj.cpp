//
// Created by adrien on 03/01/20.
//

//Export polygonal mesh to OBJ file (vertex positions, texture coordinates and vertex normals)

#include "out/WriteObj.h"

void WriteObj::exportToObj(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals)
{
    std::ofstream ofs;
    ofs.open("./polyMesh.obj", std::ios_base::out);

    ofs << "# polymesh.obj" << std::endl;
    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;
    for (int i = 0; i < _nbFace * 3; i++)
    {
        maxX = std::max(maxX, vertices[i].x);
        maxY = std::max(maxY, vertices[i].y);
        maxZ = std::max(maxZ, vertices[i].z);
    }
    for (int i = 0; i < _nbFace * 3; i++)
        ofs << "v " << -vertices[i].x  << " " << vertices[i].y << " " << vertices[i].z<< std::endl;

    for (int i = 0; i < _nbFace; i++)
        ofs << "n " << normals[i].x << " " << normals[i].y << " " << normals[i].z << std::endl;


    for (int i = 1; i < _nbFace * 3; i += 3)
    {
        ofs << "f " << i << " " << i + 1 << " " << i + 2 << std::endl;
    }
    ofs.close();
}

