
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


    /*Diamond diams(0.55f, 7);
    diams.fillMap();
    diams.updateVertices(5, 250);*/
    Perlin p;

    _shader.use();

    _shader.setVec3("lightDir", _light._lightDir);
    _shader.setFloat("ambiantCoeff", _light._ambiantCoeff);
    _shader.setVec3("lightColor", _light._lightColor);
    _shader.setFloat("specularStrength", _light._specularStrenght);


    for (const auto &vertex : p._vertices)
    {
        _vertices.push_back(vertex.x);
        _vertices.push_back(vertex.y);
        _vertices.push_back(vertex.z);
    }
    for (const auto &color : p._colors)
    {
        _colours.push_back(color.x);
        _colours.push_back(color.y);
        _colours.push_back(color.z);
    }
    for (const auto &normal : p._normals)
    {
        for (int i = 0; i < 3; i++)
        {
            _normals.push_back(normal.x);
            _normals.push_back(normal.y);
            _normals.push_back(normal.z);
        }
    }
}

void    L_OpenGL::initShader(const glm::mat4 &projection)
{
    _shader.setMat4("projection", projection);

}

void    L_OpenGL::updateShader(const glm::vec3 &dirLook, const glm::mat4 &view)
{
    _shader.use();
    _shader.setVec3("cameraDir", dirLook);
    _shader.setMat4("view", view);
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

void L_OpenGL::setDir(const glm::vec3 &dir)
{
    _light.setDir(dir);
    _shader.setVec3("lightDir", _light._lightDir);
}

void L_OpenGL::setColor(const glm::vec3 &color)
{
    _light.setColor(color);
    _shader.setVec3("lightColor", _light._lightColor);
}

void L_OpenGL::setAmbient(float ambiant)
{
    _light.setAmbient(ambiant);
    _shader.setFloat("ambiantCoeff", _light._ambiantCoeff);
}

void L_OpenGL::setSpecular(float specular)
{
    _light.setSpecular(specular);
    _shader.setFloat("specularStrength", _light._specularStrenght);
}