//
// Created by adrien on 17/02/20.
//

#ifndef INC_71K2LEDEB_MENU_H
#define INC_71K2LEDEB_MENU_H

#include "encapsulation/VertexArray.h"
#include "encapsulation/Shader.h"

class Menu
{
public:
    Shader              _textShader;
    Layout              _bufferLayout;
    VertexArray         _vArray;

    std::vector<float>  _textVertices;
    unsigned int        _vertexNb;

public:
    Menu(const std::string &, const std::string &);
    void    linkTextureInfo();
    void    initTexture();
    void click(const glm::vec2 &);
};

#endif //INC_71K2LEDEB_MENU_H
