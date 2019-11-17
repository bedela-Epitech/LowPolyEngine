

#ifndef _L_OPENGL_HPP_

#define _L_OPENGL_HPP_

#include <vector>
#include "Shader.h"
#include "map/Diamond.hpp"

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
};

#endif // _L_OPENGL_HPP_
