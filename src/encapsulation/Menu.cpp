//
// Created by adrien on 17/02/20.
//

#include "encapsulation/Menu.h"

Menu::Menu(const std::string &textVsPath, const std::string &testFsPath)
: _textShader(textVsPath, testFsPath), _bufferLayout(_textShader.ID)
{
    _textShader.use();
    _bufferLayout.addElement<float>("aPos", 2, GL_FALSE);
    _bufferLayout.addElement<float>("textCoord", 2, GL_FALSE);

    initTexture();
}

void    Menu::linkTextureInfo()
{
    _textShader.use();
    _vArray.addVertexBuffer(_textVertices.data(), sizeof(float) * _textVertices.size(), _bufferLayout);
}

void    Menu::initTexture()
{

    _textVertices = {
            -1.f, -1.f, 0.f, 0.f,
            1.f, -1.f, 1.f, 0.f,
            1.f, 1.f, 1.f, 1.f,

            -1.f, 1.f, 0.f, 1.f,
            -1.f, -1.f, 0.f, 0.f,
            1.f, 1.f, 1.f, 1.f,
    };

    _vertexNb = _textVertices.size() / 2;

    linkTextureInfo();
}


void Menu::click(const glm::vec2 &mousePos)
{
    std::cout << "mousePos = " << mousePos.x << " " << mousePos.y << std::endl;
}