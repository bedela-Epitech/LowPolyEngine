

#ifndef _L_OPENGL_HPP_

#define _L_OPENGL_HPP_

#include <vector>
#include "Shader.h"
#include "map/Diamond.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class L_OpenGL
{
public:
    Shader              _shader;

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
};

#endif // _L_OPENGL_HPP_
