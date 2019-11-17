
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
	std::map<int, std::function<void(GLFWwindow *, const float &)>> _cameraFunctions;

public:
	Input(Camera *camera);

	void	KeyManager(GLFWwindow *);
};


#endif		// !_LEDEB_INPUT_HPP_
