

#ifndef _L_OPENGL_HPP_

#define _L_OPENGL_HPP_

#include <vector>
#include "Shader.h"
#include "Light.hpp"
#include "map/Chunk.h"

class L_OpenGL
{
public:
    Shader              _shader;
    Light               _light;

    std::vector<float>  _vertices;
    std::vector<float>  _colours;
    std::vector<float>  _normals;

    unsigned int        _VBO;
    unsigned int        _VAO;




public:
    L_OpenGL(const std::string &, const std::string &);

    void    linkVertices();
    void    linkColors();
    void    linkNormals();

    void    initShader(const glm::mat4 &);
    void    updateShader(const glm::vec3 &, const glm::mat4 &);

    void    display();
    void    cleanUp();

    void setDir(const glm::vec3 &);
    void setColor(const glm::vec3 &);
    void setAmbient(float);
    void setSpecular(float);
};

#endif // _L_OPENGL_HPP_
