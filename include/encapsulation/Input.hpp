
#ifndef		_LEDEB_INPUT_HPP_
#define		_LEDEB_INPUT_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <functional>
#include <map>
#include <utility>

#include "engine/Camera.hpp"

class Input
{
private:
	std::map<sf::Keyboard::Key, std::function<void(const float &)>> _cameraFunctions;
	std::map<sf::Keyboard::Key, bool> _isPressed;

public:
	sf::Event _event;
	
public:
	Input(Camera *camera);
	~Input();

	void	KeyManager(bool &running);

};


#endif		// !_LEDEB_INPUT_HPP_
