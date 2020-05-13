//
// Created by adrien on 17/02/20.
//

#ifndef INC_71K2LEDEB_MENU_H
#define INC_71K2LEDEB_MENU_H

#include <memory>
#include "encapsulation/GUI.h"
#include "encapsulation/Window.h"

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
    GUI                 _gui;
    Texture             _menuTexture;
    Texture             _loadingTexture;

    bool                _linkDone = false;

    // GUI
    Box     _start;
    Box     _quit;

public:
    Menu(const std::string &, const std::string &, const std::string &, const std::string &);
    void    click();
    void    useShader() const;
};

#endif //INC_71K2LEDEB_MENU_H
