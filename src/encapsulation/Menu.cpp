//
// Created by adrien on 17/02/20.
//

#include "encapsulation/Menu.h"

Menu::Menu(const std::string &textVsPath, const std::string &testFsPath)
        : _textShader(textVsPath, testFsPath), _bufferLayout(_textShader.ID),
            _start(glm::vec2(200, 200), 200), _quit(glm::vec2(200, 200), 200)
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
    if (_start.isInside(mousePos))
        std::cout << "start" << std::endl;
    if (_quit.isInside(mousePos))
        std::cout << "quit" << std::endl;
}

/////////////////
//
//      BOX
//
/////////////////

Box::Box(const glm::vec2 &leftBotCorner, unsigned int size)
        : _leftBotCorner(leftBotCorner), _size(size)
{ }

bool Box::isInside(const glm::vec2 &pos)
{
    return  (pos.x >= _leftBotCorner.x && pos.y >= _leftBotCorner.y &&
             pos.x <= _leftBotCorner.x + _size && pos.y <= _leftBotCorner.y + _size);

}