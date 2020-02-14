
#ifndef		_LEDEB_INPUT_HPP_
#define		_LEDEB_INPUT_HPP_

#include <functional>
#include <map>
#include <utility>

#include "engine/Camera.hpp"

class Input
{
private:
    float               _deltaTime = 0.f;
    float               _lastFrame = 0.f;
	std::vector<int>	keys;
	std::map<int, std::function<void(const float &)>> _cameraFunctions;

public:
	Input(const std::shared_ptr<Camera> &);

	void	keyManager();
	void	mouseManger();
};


#endif		// !_LEDEB_INPUT_HPP_
