
#include "encapsulation/L_OpenGL.hpp"

/////////////////////
//
//	INIT
//
/////////////////////

L_OpenGL::L_OpenGL(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
: _shader(vertexShaderPath, fragmentShaderPath)
{
    glEnable(GL_DEPTH_TEST);


    Diamond diams(0.75f, 65);
    diams.fillMap();
    diams.updateVertices(5, 250);
    diams.updateTriangles();

    _shader.use();

    _shader.setVec3("lightDir", glm::normalize(glm::vec3(0, 1, 0)));
    _shader.setFloat("ambiantCoeff", 0.3);
    _shader.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
    _shader.setFloat("specularStrength", 0.5);



    float inc = 1.f / (diams._triangles.size() * 9);
    float color = 0.f;
    glm::vec3 normal;
    for (const auto &triangle : diams._triangles)
    {
        auto v0 = glm::vec3(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z);
        auto v1 = glm::vec3(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z);
        auto v2 = glm::vec3(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z);
        normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        for (const auto &vertex : triangle.vertices)
        {
            _vertices.push_back(vertex.x);
            _vertices.push_back(vertex.y);
            _vertices.push_back(vertex.z);

            _colours.push_back(0.5f);
            _colours.push_back(color);
            _colours.push_back(0.5f);

            _normals.push_back(normal.x);
            _normals.push_back(normal.y);
            _normals.push_back(normal.z);


            color += inc;
        }
    }
}

void    L_OpenGL::linkVertices()
{
    auto vpos_location = glGetAttribLocation(_shader.ID, "aPos");

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(vpos_location);
}

void    L_OpenGL::linkColors()
{
    auto vcol_location = glGetAttribLocation(_shader.ID, "in_Color");

    unsigned int vertexBufferObjID;

    glGenBuffers(1, &vertexBufferObjID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _colours.size(), _colours.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(vcol_location);
}

void    L_OpenGL::linkNormals()
{
    unsigned int normalID;
    auto vnorm_location = glGetAttribLocation(_shader.ID, "normal");

    glGenBuffers(1, &normalID);
    glBindBuffer(GL_ARRAY_BUFFER, normalID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _normals.size(), _normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(vnorm_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(vnorm_location);
}

void    L_OpenGL::display()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(_VAO);

    glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 3);
}

void    L_OpenGL::cleanUp()
{
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
}