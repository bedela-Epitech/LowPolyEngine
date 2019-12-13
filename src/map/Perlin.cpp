//
// Created by adrien on 13/12/19.
//

#include "map/Perlin.h"



#define ANALYTICAL_NORMALS 1







//Export polygonal mesh to OBJ file (vertex positions, texture coordinates and vertex normals)

void PolyMesh::exportToObj()
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
}

//Simple function to create a polygonal grid centred around the origin

PolyMesh* createPolyMesh(
        uint32_t width = 1,
        uint32_t height = 1,
        uint32_t subdivisionWidth = 40,
        uint32_t subdivisionHeight = 40)
{
    PolyMesh *poly = new PolyMesh;
    poly->numVertices = (subdivisionWidth + 1) * (subdivisionHeight + 1);
    std::cerr << poly->numVertices << std::endl;
    poly->vertices = new Vec3f[poly->numVertices];
    poly->normals = new Vec3f[poly->numVertices];
    poly->st = new Vec2f[poly->numVertices];
    float invSubdivisionWidth = 1.f / subdivisionWidth;
    float invSubdivisionHeight = 1.f / subdivisionHeight;
    for (uint32_t j = 0; j <= subdivisionHeight; ++j) {
        for (uint32_t i = 0; i <= subdivisionWidth; ++i) {
            poly->vertices[j * (subdivisionWidth + 1) + i] = Vec3f(width * (i * invSubdivisionWidth - 0.5), 0, height * (j * invSubdivisionHeight - 0.5));
            poly->st[j * (subdivisionWidth + 1) + i] = Vec2f(i * invSubdivisionWidth, j * invSubdivisionHeight);
        }
        std::cerr << std::endl;
    }

    poly->numFaces = subdivisionWidth * subdivisionHeight;
    poly->faceArray = new uint32_t[poly->numFaces];
    for (uint32_t i = 0; i < poly->numFaces; ++i)
        poly->faceArray[i] = 4;

    poly->verticesArray = new uint32_t[4 * poly->numFaces];
    for (uint32_t j = 0, k = 0; j < subdivisionHeight; ++j) {
        for (uint32_t i = 0; i < subdivisionWidth; ++i) {
            poly->verticesArray[k] = j * (subdivisionWidth + 1) + i;
            poly->verticesArray[k + 1] = j * (subdivisionWidth + 1) + i + 1;
            poly->verticesArray[k + 2] = (j + 1) * (subdivisionWidth + 1) + i + 1;
            poly->verticesArray[k + 3] = (j + 1) * (subdivisionWidth + 1) + i;
            k += 4;
        }
    }

    return poly;
}


Perlin::Perlin()
{
    PerlinNoise noise;

    PolyMesh *poly = createPolyMesh(3, 3, 30, 30);

    // displace and compute analytical normal using noise function partial derivatives
    Vec3f derivs;
    for (uint32_t i = 0; i < poly->numVertices; ++i) {
        Vec3f p((poly->vertices[i].x + 0.5), 0, (poly->vertices[i].z + 0.5));
        poly->vertices[i].y = noise.eval(p, derivs);
#if ANALYTICAL_NORMALS
        Vec3f tangent(1, derivs.x, 0); // tangent
        Vec3f bitangent(0, derivs.z, 1); // bitangent
        // equivalent to bitangent.cross(tangent)
        poly->normals[i] = Vec3f(-derivs.x, 1, -derivs.z);
        poly->normals[i].normalize();
#endif
    }

#if !ANALYTICAL_NORMALS
    // compute face normal if you want
    for (uint32_t k = 0, off = 0; k < poly->numFaces; ++k) {
        uint32_t nverts = poly->faceArray[k];
        const Vec3f &va = poly->vertices[poly->verticesArray[off]];
        const Vec3f &vb = poly->vertices[poly->verticesArray[off + 1]];
        const Vec3f &vc = poly->vertices[poly->verticesArray[off + nverts - 1]];

        Vec3f tangent = vb - va;
        Vec3f bitangent = vc - va;

        poly->normals[poly->verticesArray[off]] = bitangent.cross(tangent);
        poly->normals[poly->verticesArray[off]].normalize();

        off += nverts;
    }
#endif

    poly->exportToObj();
    delete poly;

    // output noise map to PPM
    const uint32_t width = 512, height = 512;
    float  *noiseMapPtr = new float[width * height];
    std::vector<std::vector<float>> noiseMap;
    std::vector<float> lineMap;
    /*for (uint32_t j = 0; j < height; ++j)
    {
        for (uint32_t i = 0; i < width; ++i)
        {
            lineMap.push_back((noise.eval(Vec3f(i, 0, j) * (1 / 64.), derivs) + 1) * 0.5f);
        }
        noiseMap.push_back(lineMap);
        lineMap.clear();
    }*/

    uint32_t numLayers = 5;
    float maxVal = 0;
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            float fractal = 0;
            float amplitude = 1;
            Vec3f pt = Vec3f(i, 0, j) * (1 / 128.f);
            for (uint32_t k = 0; k < numLayers; ++k) {
                fractal += (1 + noise.eval(pt, derivs)) * 0.5 * amplitude;
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
        noiseMap.push_back(lineMap);
        lineMap.clear();
    }
    std::cout << "end" << std::endl;

    float scale = 5;
    float smooth = 250;
    float inc = 0.5f / (noiseMap.size() * noiseMap.size());
    float color = 0.f;
    for (int x = 0; x < noiseMap.size() - 1; x++)
    {
        for (int z = 0; z < noiseMap.size() - 1; z++)
        {

            glm::vec3 v0(x * scale, noiseMap[x][z + 1] * smooth - 100, (z + 1) * scale);
            glm::vec3 v1((x + 1) * scale, noiseMap[x + 1][z] * smooth - 100, z * scale);
            glm::vec3 v2(x * scale, noiseMap[x][z] * smooth - 100, z * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));



            v0 = glm::vec3((x + 1) * scale, noiseMap[x + 1][z + 1] * smooth - 100, (z + 1) * scale);
            v1 = glm::vec3((x + 1) * scale, noiseMap[x + 1][z] * smooth - 100, z * scale);
            v2 = glm::vec3(x * scale, noiseMap[x][z + 1] * smooth - 100, (z + 1) * scale);
            _vertices.push_back(v0);
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _colors.emplace_back(0.5f, color, 0.5f);
            _normals.push_back(glm::normalize(glm::cross(v1 - v0, v2 - v0)));

            color += inc;
        }
    }
}
