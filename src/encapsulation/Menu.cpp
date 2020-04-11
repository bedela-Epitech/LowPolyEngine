//
// Created by adrien on 17/02/20.
//

#include "encapsulation/Menu.h"

Menu::Menu(const std::string &textVsPath, const std::string &testFsPath, const std::string &menuTextPath, const std::string &loadingTextPath)
        : _textShader(textVsPath, testFsPath), _menuTexture(menuTextPath), _loadingTexture(loadingTextPath), _bufferLayout(_textShader.ID),
          _start(glm::vec2(142, 85), glm::vec2(670, 140)), _quit(glm::vec2(145, 305), glm::vec2(670, 140))
{
    _textShader.use();

    try {
    _bufferLayout.addElement<float>("aPos", 2, GL_FALSE);
    _bufferLayout.addElement<float>("textCoord", 2, GL_FALSE);
    }
    catch (const std::invalid_argument &error) {
        throw std::invalid_argument("in Menu, invalid shader variable name");
    }

    initTexture();
    bindTexture(_menuTexture);
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

void    Menu::linkTextureInfo()
{
    _textShader.use();
    _vArray.addVertexBuffer(_textVertices.data(), sizeof(float) * _textVertices.size(), _bufferLayout);
}

void Menu::bindTexture(Texture &texture)
{
    unsigned int textureID = texture.bind();
    _textShader.use();
    _textShader.setInt("u_Texture", textureID);
}

void Menu::click()
{
    auto mousePos = Window::getCursorPos();
    if (_start.isInside(mousePos))
    {
        _linkDone = true;
        bindTexture(_loadingTexture);
        Window::hideCursor();
    }
    if (_quit.isInside(mousePos))
        Window::close();
}

/////////////////
//
//      BOX
//
/////////////////

Box::Box(const glm::vec2 &leftBotCorner, const glm::vec2 &size)
        : _leftBotCorner(leftBotCorner), _size(size)
{ }

bool Box::isInside(const glm::vec2 &pos)
{
    return  (pos.x >= _leftBotCorner.x && pos.y >= _leftBotCorner.y &&
             pos.x <= _leftBotCorner.x + _size.x && pos.y <= _leftBotCorner.y + _size.y);

}