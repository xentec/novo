#pragma once

#include "novo/global.h"
#include "novo/exception.h"

#include <GLFW/glfw3.h>

namespace novo {
namespace window {

struct Config {
	bool resizable = true;
	bool visible = true;
	bool decorated = true;

	struct Bits {
		i32
			red = 8,
			green = 8,
			blue = 8,
			alpha = 8;
		i32
			depth = 24,
			stencil = 8;
	} bits;

	i32 auxBuffers = 0;
	i32 samples = 0;
	i32 refreshRate = 0;

	struct Version {
		i32 major, minor;
	} GLversion = { 1, 0 };

	enum class Robustness : i32 {
		NONE = GLFW_NO_ROBUSTNESS,
		NO_RESET_NOTIFICATION = GLFW_NO_RESET_NOTIFICATION,
		LOSE_CONTEXT_ON_RESET = GLFW_LOSE_CONTEXT_ON_RESET
	} GLrobustness = Robustness::NONE;

	enum class Profile : i32 {
		ANY = GLFW_OPENGL_ANY_PROFILE,
		CORE = GLFW_OPENGL_CORE_PROFILE,
		COMPAT = GLFW_OPENGL_COMPAT_PROFILE
	} GLprofile = Profile::ANY;

	bool forwarded = false;
	bool debugging = false;
};

}


struct Window
{
	enum class CursorMode {
		NORMAL = GLFW_CURSOR_NORMAL,
		HIDDEN = GLFW_CURSOR_HIDDEN,
		DISABLED = GLFW_CURSOR_DISABLED
	};

	enum class Attribute {
		Focused = GLFW_FOCUSED,
		Decorated = GLFW_DECORATED,
		Resizeable = GLFW_RESIZABLE,
		Visible = GLFW_VISIBLE,
		Minimized = GLFW_ICONIFIED
	};

	Window(i32 width, i32 height, const string &title, const window::Config &setup = window::Config());
	virtual ~Window();
	Window(const Window &other);
	Window& operator=(const Window& other);

	void open(bool fullscreen = false, Window* shared = nullptr);
	bool isOpen();
	void close();
	void bindContext();
	void present();
	void show();
	void hide();

	string getTitle() const;
	void setTitle(const string &newTitle);

	void setSize(i32 width, i32 height);
	void getSize(i32& width, i32& height) const;

	bool is(Attribute attr);

	void setCursorMode(CursorMode mode);
	CursorMode getCursorMode() const;

	void setCursorPos(f64 x, f64 y);
	void getCursorPos(f64& x, f64& y) const;

	static void setVsync(i32 interval);

	operator GLFWwindow*() const;

	window::Config setup;
private:
	struct {
		i32 width, height;
		string title;
	} initial;

	GLFWwindow* window;
};


class WindowException : public Exception {
public:
	WindowException(const Window* window, string reason):
		Exception(reason),
		window(window) {}

	const Window* window;
};


}
