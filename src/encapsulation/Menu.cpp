//
// Created by adrien on 17/02/20.
//

#include "encapsulation/Menu.h"

Menu::Menu()
{

}

void Menu::click(const glm::vec2 &mousePos)
{
    std::cout << "mousePos = " << mousePos.x << " " << mousePos.y << std::endl;
}