//
// Created by adrien on 03/01/20.
//

//Export polygonal mesh to OBJ file (vertex positions, texture coordinates and vertex normals)

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>

std::tuple<uint32_t*, uint32_t *> createPolyMesh(const std::vector<std::vector<float>> &vertices, unsigned int width, unsigned int height)
{
    auto numFaces = width * height;
    auto faceArray = new uint32_t[numFaces];
    for (uint32_t i = 0; i < numFaces; ++i)
        faceArray[i] = 4;

    auto verticesArray = new uint32_t[4 * numFaces];
    for (uint32_t j = 0, k = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            verticesArray[k] = j * (width + 1) + i;
            verticesArray[k + 1] = j * (width + 1) + i + 1;
            verticesArray[k + 2] = (j + 1) * (width + 1) + i + 1;
            verticesArray[k + 3] = (j + 1) * (width + 1) + i;
            k += 4;
        }
    }

    return {verticesArray, faceArray};
}

void exportToObj(const std::vector<glm::vec3> &vertices)
{
    std::ofstream ofs;
    ofs.open("./polyMesh.obj", std::ios_base::out);

    int width = vertices.size();
    int numVertices = vertices.size() * vertices.front().size();
    auto [verticesArray, faceArray] = createPolyMesh(vertices, vertices.size(), vertices.size());

    for (uint32_t i = 0; i < numVertices; ++i) {
        ofs << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl ;
    }

    for (uint32_t i = 0; i < numVertices; ++i) {
        ofs << "vt " << st[i].x << " " << st[i].y << std::endl;
    }

    for (uint32_t i = 0; i < numVertices; ++i) {
        ofs << "vn " << normals[i].x << " " << normals[i].y << " " << normals[i].z << std::endl;
    }

    /*for (uint32_t i = 0, k = 0; i < numFaces; ++i) {
        ofs << "f ";
        for (uint32_t j = 0; j < faceArray[i]; ++j) {
            uint32_t objIndex = verticesArray[k + j] + 1;
            ofs << objIndex << "/" << objIndex << "/" << objIndex << ((j == (faceArray[i] - 1)) ? "" : " ");
        }
        ofs << std::endl;
        k += faceArray[i];
    }*/

    ofs.close();
}

