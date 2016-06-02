#include "window.h"

#include <iostream>

using namespace novo;
using namespace novo::window;

#ifdef OS_LINUX
	#define GLFW_EXPOSE_NATIVE_X11 1
	#define GLFW_EXPOSE_NATIVE_GLX 1
namespace ext {
	#include <GLFW/glfw3native.h>
}
#endif

static void setWindowHints(const Config& cfg);
static void setXClassHint(const Window* window);

Window::Window(i32 width, i32 height, const string &title, const Config &setup)
	: setup(setup), initial { width, height, title }, window(nullptr)
{}

Window::~Window()
{
	close();
}

Window::Window(const Window &other)
{
	initial = other.initial;
	setup = other.setup;
	window = other.window;
}

Window& Window::operator=(const Window& other)
{
	close();
	initial = other.initial;
	setup = other.setup;
	window = other.window;
	return *this;
}

void Window::open(bool fullscreen, Window* shared)
{
	if(window) return;

	GLFWmonitor* monitor = nullptr;
	if(fullscreen)
		monitor = glfwGetPrimaryMonitor();

	setWindowHints(setup);
	window = glfwCreateWindow(initial.width, initial.height, initial.title.c_str(), monitor, shared ? shared->window : nullptr);
	if(!window)
		throw WindowException(this, "glfwCreateWindow() failed");

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
	if(window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}
}

void Window::bindContext()
{
	glfwMakeContextCurrent(window);
}

void Window::present()
{
	glfwSwapBuffers(window);
}

void Window::show()
{
	glfwShowWindow(window);
}

void Window::hide()
{
	glfwHideWindow(window);
}


string Window::getTitle() const
{
	return initial.title;
}

void Window::setTitle(const string &newTitle)
{
	initial.title = newTitle;
	if(isOpen())
		glfwSetWindowTitle(window, newTitle.c_str());
}

void Window::setSize(i32 width, i32 height)
{
	glfwSetWindowSize(window, width, height);
}

void Window::getSize(i32& width, i32& height) const
{
	glfwGetWindowSize(window, &width, &height);
}

bool Window::is(Attribute attr)
{
	return glfwGetWindowAttrib(window, static_cast<int>(attr));
}


void Window::setCursorMode(CursorMode mode)
{
	glfwSetInputMode(window, GLFW_CURSOR, static_cast<int>(mode));
}

Window::CursorMode Window::getCursorMode() const
{
	return static_cast<CursorMode>(glfwGetInputMode(window, GLFW_CURSOR));
}

void Window::setCursorPos(f64 x, f64 y)
{
	glfwSetCursorPos(window, x, y);
}

void Window::getCursorPos(f64& x, f64& y) const
{
	glfwGetCursorPos(window, &x, &y);
}


Window::operator GLFWwindow*() const
{
	return window;
}

void Window::setVsync(i32 interval)
{
	glfwSwapInterval(interval);
}


void setWindowHints(const Config& cfg)
{
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
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, cfg.debugging);
	// Setting accuracy of colors
	glfwWindowHint(GLFW_RED_BITS, cfg.bits.red);
	glfwWindowHint(GLFW_GREEN_BITS, cfg.bits.green);
	glfwWindowHint(GLFW_BLUE_BITS, cfg.bits.blue);
	glfwWindowHint(GLFW_ALPHA_BITS, cfg.bits.alpha);
	// Setting accuracy of buffers
	glfwWindowHint(GLFW_DEPTH_BITS, cfg.bits.depth);
	glfwWindowHint(GLFW_STENCIL_BITS, cfg.bits.stencil);
	// Anti-Aliasing
	glfwWindowHint(GLFW_SAMPLES, cfg.samples);
}

#ifdef OS_LINUX
void setXClassHint(const Window *window)
{
	ext::XClassHint xch;
	xch.res_name = const_cast<char*>("gl"); // aka instance
	xch.res_class =	const_cast<char*>(window->getTitle().c_str());

	ext::XSetClassHint(ext::glfwGetX11Display(), ext::glfwGetX11Window(*window), &xch);

}
#endif



