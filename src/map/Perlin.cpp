//
// Created by adrien on 13/12/19.
//

#include "map/Perlin.h"



#define ANALYTICAL_NORMALS 1







//Export polygonal mesh to OBJ file (vertex positions, texture coordinates and vertex normals)

/*void PolyMesh::exportToObj()
{
    std::ofstream ofs;
    ofs.open("./polyMesh.obj", std::ios_base::out);

    for (uint32_t i = 0; i < numVertices; ++i) {
        ofs << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
    }

    for (uint32_t i = 0; i < numVertices; ++i) {
        ofs << "vt " << st[i].x << " " << st[i].y << std::endl;
    }

    for (uint32_t i = 0; i < numVertices; ++i) {
        ofs << "vn " << normals[i].x << " " << normals[i].y << " " << normals[i].z << std::endl;
    }

    for (uint32_t i = 0, k = 0; i < numFaces; ++i) {
        ofs << "f ";
        for (uint32_t j = 0; j < faceArray[i]; ++j) {
            uint32_t objIndex = verticesArray[k + j] + 1;
            ofs << objIndex << "/" << objIndex << "/" << objIndex << ((j == (faceArray[i] - 1)) ? "" : " ");
        }
        ofs << std::endl;
        k += faceArray[i];
    }

    ofs.close();
}*/

Perlin::Perlin(int w, int h)
{
    PerlinNoise noise;

    const uint32_t width = pow(2, w), height = pow(2, h);
    float  *noiseMapPtr = new float[width * height];
    std::vector<float> lineMap;


    uint32_t numLayers = 5;
    float maxVal = 0;
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            float fractal = 0;
            float amplitude = 1;
            glm::vec3 pt = glm::vec3(i, 0, j) * (1 / 128.f);
            for (uint32_t k = 0; k < numLayers; ++k) {
                fractal += (1 + noise.eval(pt)) * 0.5 * amplitude;
                pt *= 2;
                amplitude *= 0.5;
            }
            if (fractal > maxVal) maxVal = fractal;
            noiseMapPtr[j * width + i] = fractal;
        }
    }

    for (uint32_t i = 0; i < width * height; ++i)
        noiseMapPtr[i] /= maxVal;

    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            lineMap.push_back(noiseMapPtr[j * width + i]);
        }
        _noiseMap.push_back(lineMap);
        lineMap.clear();
    }
}
