//
// Created by adrien on 03/01/20.
//

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