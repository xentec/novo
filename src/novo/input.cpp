#include "input.h"

#include "novo/app.h"
#include "novo/window.h"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>

using namespace novo;


InputManager::InputManager(Window& window):
	EventManager(),
	window(window)
{}

InputManager::~InputManager()
{}


void InputManager::setup()
{
	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, keyCB);
	glfwSetMouseButtonCallback(window, mouseKeyCB);
	glfwSetScrollCallback(window, mouseScrollCB);

	glfwSetWindowSizeCallback(window, winSizeCB);
	glfwSetWindowFocusCallback(window, winFocusCB);
}

void InputManager::captureMouse(bool disable)
{
	glfwSetCursorPosCallback(window, mousePosCB);
	if(disable) {
		window.setCursorMode(Window::CursorMode::DISABLED);
	}
}

void InputManager::releaseMouse()
{
	glfwSetCursorPosCallback(window, nullptr);
	window.setCursorMode(Window::CursorMode::NORMAL);
}

void InputManager::poll()
{
	glfwPollEvents();
}


// ┏━╸┏━┓╻  ╻  ┏┓ ┏━┓┏━╸╻┏ ┏━┓
// ┃  ┣━┫┃  ┃  ┣┻┓┣━┫┃  ┣┻┓┗━┓
// ┗━╸╹ ╹┗━╸┗━╸┗━┛╹ ╹┗━╸╹ ╹┗━┛

inline InputManager* get(GLFWwindow* gw) { return static_cast<InputManager*>(glfwGetWindowUserPointer(gw)); }

void InputManager::keyCB(GLFWwindow* gw, int key, int scancode, int action, int mod) {
	try {
		get(gw)->emit<event::Key>(action, key, mod);
	} catch (const std::exception &e) {
		fmt::print(std::cerr, "Error in keyCB: {}", e.what());
	}
}

void InputManager::mouseKeyCB(GLFWwindow* gw, int button, int action, int mod) {
	try {
		get(gw)->emit<event::Key>(action, button, mod);
	} catch (const std::exception &e) {
		fmt::print(std::cerr, "Error in mouseBtnCB: {}", e.what());
	}
}

void InputManager::mousePosCB(GLFWwindow* gw, double x, double y) {
	try {
		get(gw)->emit<event::Cursor>(x, y);
	} catch (const std::exception &e) {
		fmt::print(std::cerr, "Error in cursorPosCB: {}", e.what());
	}
}

void InputManager::mouseScrollCB(GLFWwindow* gw, double xoff, double yoff) {
	try {
		get(gw)->emit<event::Scroll>(xoff, yoff);
	} catch (const std::exception &e) {
		fmt::print(std::cerr, "Error in mouseBtnCB: {}", e.what());
	}
}

void InputManager::winSizeCB(GLFWwindow* gw, int width, int height) {
	try {
		InputManager* ih = get(gw);
		ih->emit<event::window::Size>(ih->window, width, height);
	} catch (const std::exception &e) {
		fmt::print(std::cerr, "Error in winSizeCB: {}", e.what());
	}
}

void InputManager::winFocusCB(GLFWwindow* gw, int flag) {
	try {
		InputManager* ih = get(gw);
		ih->emit<event::window::Focus>(ih->window, static_cast<bool>(flag));
	} catch (const std::exception &e) {
		fmt::print(std::cerr, "Error in winFocusCB: {}", e.what());
	}
}

