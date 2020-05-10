//
// Created by adrien on 17/02/20.
//

#include "encapsulation/Menu.h"

Menu::Menu(const std::string &textVsPath, const std::string &testFsPath, const std::string &menuTextPath, const std::string &loadingTextPath)
        : _gui(textVsPath, testFsPath, glm::vec2(-1.f, -1.f), glm::vec2(2.f, 2.f)),
          _menuTexture(menuTextPath), _loadingTexture(loadingTextPath),
          _start(glm::vec2(142, 85), glm::vec2(670, 140)), _quit(glm::vec2(145, 305), glm::vec2(670, 140))
{
    _gui.attachTexture(_menuTexture);
}

void Menu::click()
{
    auto mousePos = Window::getCursorPos();
    if (_start.isInside(mousePos))
    {
        _linkDone = true;
        _gui.attachTexture(_loadingTexture);
        Window::hideCursor();
    }
    if (_quit.isInside(mousePos))
        Window::close();
}

void Menu::useShader() const
{
    _gui._textShader.use();
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