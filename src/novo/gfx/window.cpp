#include "window.h"

#include <iostream>

using namespace novo::graphics;
using std::string;

namespace dtl {
#ifdef OS_LINUX
	#define GLFW_EXPOSE_NATIVE_X11 1
	#define GLFW_EXPOSE_NATIVE_GLX 1

	#include <GLFW/glfw3native.h>
#endif
}

void setWindowHints(const WindowConfig &cfg);
static void setXClassHint(Window* window);

Window::Window(i32 width, i32 height, const string &title, const WindowConfig &config)
	: width(width), height(height), title(title), config(config), window(nullptr)
{}

Window::Window(const Window &other)
{
	width = other.width;
	height = other.width;
	title = other.title;
	config = other.config;
}

Window::~Window()
{
	close();
}

void Window::open(bool fullscreen)
{
	if(window) return;

	GLFWmonitor* mon = nullptr;
	if(fullscreen)
		mon = glfwGetPrimaryMonitor();

	setWindowHints(config);
	window = glfwCreateWindow(width, height, title.c_str(), mon, nullptr);
	if(!window)
		throw WindowException(this, "glfwCreateWindow() failed");

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, keyCB);
	glfwSetCursorPosCallback(window, cursorPosCB);
	glfwSetMouseButtonCallback(window, mouseBtnCB);

	setCursorMode(CursorMode::DISABLED);

#ifdef OS_LINUX
	setXClassHint(this);
#endif
}

bool Window::isOpen()
{
	return window && !glfwWindowShouldClose(window);
}

void Window::close()
{
	if(window) {
		glfwDestroyWindow(window);
		window = nullptr;
	}
}

std::string Window::getTitle() const
{
	return title;
}

void Window::setTitle(const std::string &newTitle)
{
	title = newTitle;
	if(isOpen())
		glfwSetWindowTitle(window, title.c_str());
}

void Window::setCursorMode(CursorMode mode)
{
	glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
}

CursorMode Window::getCursorMode() const
{
	return static_cast<CursorMode>(glfwGetInputMode(window, GLFW_CURSOR));
}

void Window::bindContext()
{
	glfwMakeContextCurrent(window);
}

void Window::present()
{
	glfwSwapBuffers(window);
}

Window::operator GLFWwindow*() const
{
	return window;
}

void Window::poll()
{
	glfwPollEvents();
}

void Window::setVsync(i32 interval)
{
	glfwSwapInterval(interval);
}

inline
Window* get (GLFWwindow* gw) { return static_cast<Window*>(glfwGetWindowUserPointer(gw)); }

void Window::keyCB(GLFWwindow* gw, int key, int scancode, int action, int mod) {
	try {
		get(gw)->onKey(key, scancode, action, mod);
	} catch (const std::exception &e) {
		std::cerr << "Error in keyCB: " << e.what() << std::endl;
	}
}

void Window::winSizeCB(GLFWwindow* gw, int width, int height) {
	try {
		get(gw)->onResize(width, height);
	} catch (const std::exception &e) {
		std::cerr << "Error in winSizeCB: " << e.what() << std::endl;
	}
}

void Window::winFocusCB(GLFWwindow* gw, int flag) {
	try {
		get(gw)->onFocus(flag);
	} catch (const std::exception &e) {
		std::cerr << "Error in winFocusCB: " << e.what() << std::endl;
	}
}

void Window::cursorPosCB(GLFWwindow* gw, double x, double y) {
	try {
		get(gw)->onCursorMove(x, y);
	} catch (const std::exception &e) {
		std::cerr << "Error in cursorPosCB: " << e.what() << std::endl;
	}
}

void Window::mouseBtnCB(GLFWwindow* gw, int button, int action, int mod) {
	try {
		get(gw)->onMouseButton(button, action, mod);
	} catch (const std::exception &e) {
		std::cerr << "Error in mouseBtnCB: " << e.what() << std::endl;
	}
}


void setWindowHints(const WindowConfig &cfg) {
	// Setting visual properties
	glfwWindowHint(GLFW_VISIBLE, cfg.visible);
	glfwWindowHint(GLFW_RESIZABLE, cfg.resizable);
	glfwWindowHint(GLFW_DECORATED, cfg.decorated);
	// Setting correct context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, cfg.GLversion.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, cfg.GLversion.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(cfg.GLprofile));
	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(cfg.GLrobustness));
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, cfg.forwarded);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, cfg.debuging);
	// Setting accuracy of colors
	glfwWindowHint(GLFW_RED_BITS, cfg.bits.red);
	glfwWindowHint(GLFW_GREEN_BITS, cfg.bits.green);
	glfwWindowHint(GLFW_BLUE_BITS, cfg.bits.blue);
	glfwWindowHint(GLFW_ALPHA_BITS, cfg.bits.alpha);
	// Setting accuracy of buffers
	glfwWindowHint(GLFW_DEPTH_BITS, cfg.bits.depth);
	glfwWindowHint(GLFW_STENCIL_BITS, cfg.bits.stencil);

	glfwWindowHint(GLFW_SAMPLES, cfg.samples);
}

#ifdef OS_LINUX
void setXClassHint(Window *window)
{
	dtl::XClassHint xch;
	xch.res_name = const_cast<char*>("gl"); 	// aka instance
	xch.res_class =	const_cast<char*>(window->getTitle().c_str());

	dtl::XSetClassHint(dtl::glfwGetX11Display(), dtl::glfwGetX11Window(*window), &xch);

}
#endif



