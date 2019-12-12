
#include "encapsulation/Input.hpp"

Input::Input(const std::shared_ptr<Camera> &camera)
{
	keys = std::vector<int>{GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_S,
							GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_RIGHT,
							GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN};

	_cameraFunctions[GLFW_KEY_ESCAPE] = std::bind(&Camera::closeWindow, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_W] = std::bind(&Camera::moveForward, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_S] = std::bind(&Camera::moveBack, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_A] = std::bind(&Camera::moveLeft, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_D] = std::bind(&Camera::moveRight, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_RIGHT] = std::bind(&Camera::rotateRight, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_LEFT] = std::bind(&Camera::rotateLeft, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_UP] = std::bind(&Camera::rotateUp, camera, std::placeholders::_1);
	_cameraFunctions[GLFW_KEY_DOWN] = std::bind(&Camera::rotateDown, camera, std::placeholders::_1);
}

void	Input::KeyManager()
{
	auto currentFrame = static_cast<float>(Window::getTime());
	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;

	for (const auto &key : keys)
	{
		if (Window::getKey(key) == GLFW_PRESS)
			_cameraFunctions[key](_deltaTime);
	}

}