
#include "encapsulation/Input.h"

using namespace std::placeholders;

Input::Input(const std::shared_ptr<Camera> &camera, const std::shared_ptr<Menu> &menu)
{
	_keys = {GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_S,
			 GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_RIGHT,
			 GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN};

	_cameraFunctions[GLFW_KEY_ESCAPE] = std::bind(&Camera::closeWindow, camera, _1);
	_cameraFunctions[GLFW_KEY_W] = std::bind(&Camera::moveForward, camera, _1);
	_cameraFunctions[GLFW_KEY_S] = std::bind(&Camera::moveBack, camera, _1);
	_cameraFunctions[GLFW_KEY_A] = std::bind(&Camera::moveLeft, camera, _1);
	_cameraFunctions[GLFW_KEY_D] = std::bind(&Camera::moveRight, camera, _1);
	_cameraFunctions[GLFW_KEY_RIGHT] = std::bind(&Camera::rotateRight, camera, _1);
	_cameraFunctions[GLFW_KEY_LEFT] = std::bind(&Camera::rotateLeft, camera, _1);
	_cameraFunctions[GLFW_KEY_UP] = std::bind(&Camera::rotateUp, camera, _1);
	_cameraFunctions[GLFW_KEY_DOWN] = std::bind(&Camera::rotateDown, camera, _1);

	_mouseButtons = { GLFW_MOUSE_BUTTON_LEFT };

	_menuFunctions[GLFW_MOUSE_BUTTON_LEFT] = std::bind(&Menu::click, menu);
}

void	Input::keyManager()
{
	auto currentFrame = static_cast<float>(Window::getTime());
	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;

	for (const auto &key : _keys)
	{
		if (Window::getKey(key) == GLFW_PRESS)
			_cameraFunctions[key](_deltaTime);
	}
}

void	Input::mouseManger()
{
	for (const auto &mouseButton : _mouseButtons)
	{
		if (Window::getMouseClick(mouseButton) == GLFW_PRESS)
			_menuFunctions[mouseButton]();
	}
}