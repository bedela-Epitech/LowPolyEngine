
#include "encapsulation/Window.hpp"
#include "encapsulation/Input.hpp"
#include <iostream>

Input::Input(Camera *camera)
{
	_cameraFunctions[sf::Keyboard::Key::S] = std::bind(&Camera::moveBack, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::Z] = std::bind(&Camera::moveForward, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::Q] = std::bind(&Camera::moveLeft, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::D] = std::bind(&Camera::moveRight, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::Left] = std::bind(&Camera::rotateLeft, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::Right] = std::bind(&Camera::rotateRight, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::Up] = std::bind(&Camera::rotateUp, camera, std::placeholders::_1);
	_cameraFunctions[sf::Keyboard::Key::Down] = std::bind(&Camera::rotateDown, camera, std::placeholders::_1);

	_isPressed[sf::Keyboard::Key::S] = false;
	_isPressed[sf::Keyboard::Key::Z] = false;
	_isPressed[sf::Keyboard::Key::Q] = false;
	_isPressed[sf::Keyboard::Key::D] = false;
	_isPressed[sf::Keyboard::Key::Left] = false;
	_isPressed[sf::Keyboard::Key::Up] = false;
	_isPressed[sf::Keyboard::Key::Down] = false;
	_isPressed[sf::Keyboard::Key::Right] = false;
}

Input::~Input()
{
}

void	Input::KeyManager(bool &running)
{
	if (_event.key.code == sf::Keyboard::Escape || _event.type == sf::Event::Closed)
	{
		running = false;
		return;
	}
	if (_cameraFunctions.find(_event.key.code) != _cameraFunctions.end() && _event.type == sf::Event::KeyPressed)
	{
		_isPressed[_event.key.code] = true;
	}
	if (_cameraFunctions.find(_event.key.code) != _cameraFunctions.end() && _event.type == sf::Event::KeyReleased)
	{
		_isPressed[_event.key.code] = false;
	}
	for (const auto &keyStat : _isPressed)
	{
		if (keyStat.second == true)
			_cameraFunctions[keyStat.first](5.f);
	}

}