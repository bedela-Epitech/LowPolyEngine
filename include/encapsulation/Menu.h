//
// Created by adrien on 17/02/20.
//

#ifndef INC_71K2LEDEB_MENU_H
#define INC_71K2LEDEB_MENU_H

#include "encapsulation/VertexArray.h"
#include "encapsulation/Shader.h"
#include "encapsulation/Window.hpp"
#include "encapsulation/Texture.h"

class Box
{
private:
    glm::vec2       _leftBotCorner;
    glm::vec2       _size;
public:
    Box(const glm::vec2 &, const glm::vec2 &);

    bool isInside(const glm::vec2 &);
};

class Menu
{
public:
    Shader              _textShader;
    Texture             _menuTexture;
    Texture             _loadingTexture;
    Layout              _bufferLayout;
    VertexArray         _vArray;

    std::vector<float>  _textVertices;
    unsigned int        _vertexNb;

    bool                _linkDone = false;

    // GUI
    Box     _start;
    Box     _quit;

public:
    Menu(const std::string &, const std::string &, const std::string &, const std::string &);
    void    linkTextureInfo();
    void    initTexture();
    void    click();
    void    bindTexture(Texture &);
};

#endif //INC_71K2LEDEB_MENU_H
