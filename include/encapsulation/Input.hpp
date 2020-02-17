
#ifndef		_LEDEB_INPUT_HPP_
#define		_LEDEB_INPUT_HPP_

#include <functional>
#include <map>
#include <utility>

#include "encapsulation/Menu.h"
#include "engine/Camera.hpp"

class Input
{
private:
    float               _deltaTime = 0.f;
    float               _lastFrame = 0.f;
    std::vector<int>	_keys;
    std::vector<int>	_mouseButtons;
    std::map<int, std::function<void(float)>>       _cameraFunctions;
    std::map<int, std::function<void(const glm::vec2 &)>>    _menuFunctions;

public:
	Input(const std::shared_ptr<Camera> &,
		  const std::shared_ptr<Menu> &);

	void	keyManager();
	void	mouseManger();
};


#endif		// !_LEDEB_INPUT_HPP_
