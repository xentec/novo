#ifndef WINDOW_H
#define WINDOW_H

#include <novo/global.h>
#include <novo/exception.h>

#define BOOST_BIND_NO_PLACEHOLDERS
#include <boost/signals2.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace novo {
namespace graphics {

using boost::signals2::signal;

enum class CursorMode : int {
	NORMAL = GLFW_CURSOR_NORMAL,
	HIDDEN = GLFW_CURSOR_HIDDEN,
	DISABLED = GLFW_CURSOR_DISABLED
};


struct WindowConfig {
	bool resizable = true;
	bool visible = true;
	bool decorated = true;

	struct Bits {
		int
			red = 8,
			green = 8,
			blue = 8,
			alpha = 8;
		int
			depth = 24,
			stencil = 8;
	} bits;

	int auxBuffers = 0;
	int samples = 0;
	int refreshRate = 0;

	struct Version {
		int major, minor;
	} GLversion = { 1, 0 };

	enum class Robustness : int {
		NONE = GLFW_NO_ROBUSTNESS,
		NO_RESET_NOTIFICATION = GLFW_NO_RESET_NOTIFICATION,
		LOSE_CONTEXT_ON_RESET = GLFW_LOSE_CONTEXT_ON_RESET
	} GLrobustness = Robustness::NONE;

	enum class Profile : int {
		ANY = GLFW_OPENGL_ANY_PROFILE,
		CORE = GLFW_OPENGL_CORE_PROFILE,
		COMPAT = GLFW_OPENGL_COMPAT_PROFILE
	} GLprofile = Profile::ANY;

	bool forwarded = false;
	bool debuging = false;

	CursorMode cursorMode = CursorMode::NORMAL;
};

class Window {
public:
	Window(int width, int height, const string &title, const WindowConfig &config = WindowConfig());
	Window(const Window &other);
	~Window();

	void open(bool fullscreen = false);
	bool isOpen();
	void close();
	void bindContext();
	void present();

	std::string getTitle() const;
	void setTitle(const string &newTitle);

	void setCursorMode(CursorMode mode);
	CursorMode getCursorMode() const;

	WindowConfig config;

	static void poll();
	static void setVsync(int interval);

	operator GLFWwindow*() const;


	typedef signal<void(i32,i32)> onMoveSIG;
	typedef signal<void(i32,i32)> onResizeSIG;
	typedef signal<void()> onCloseSIG;
	typedef signal<void()> onRefreshSIG;
	typedef signal<void(bool)> onFocusSIG;
	typedef signal<void(bool)> onIconifySIG;

	typedef signal<void(i32,i32)> onFramebufferResizeSIG;

	typedef signal<void(i32,i32,i32)> onMouseButtonSIG;
	typedef signal<void(f64,f64)> onCursorMoveSIG;
	typedef signal<void(i32)> onCursorEnterSIG;
	typedef signal<void(f64,f64)> onScrollSIG;

	typedef signal<void(i32,i32,i32,i32)> onKeySIG;
	typedef signal<void(u32)> onCharSIG;

	typedef signal<void(i32)> onMonitorStatusSIG;

	onMoveSIG onMove;
	onResizeSIG onResize;
	onCloseSIG onClose;
	onRefreshSIG onRefresh;
	onFocusSIG onFocus;
	onIconifySIG onIconify;

	onFramebufferResizeSIG onFramebufferResize;

	onMouseButtonSIG onMouseButton;
	onCursorMoveSIG onCursorMove;
	onCursorEnterSIG onCursorEnter;
	onScrollSIG onScroll;

	onKeySIG onKey;
	onCharSIG onChar;

	onMonitorStatusSIG onMonitorStatus;

private:
	int width, height;
	string title;

	GLFWwindow* window;


	static void keyCB(GLFWwindow* gw, int key, int scancode, int action, int mod);
	static void winSizeCB(GLFWwindow* gw, int width, int height);
	static void cursorPosCB(GLFWwindow* gw, double x, double y);
	static void mouseBtnCB(GLFWwindow* gw, int button, int action, int mod);
	static void winFocusCB(GLFWwindow* gw, int flag);
};

class WindowException : public NovoException {
	const Window* win;
public:
	WindowException(const Window* window, std::string reason):
		NovoException(reason),
		win(window) {}
	const Window* getWindow() const { return win; }
};


}
}
#endif // WINDOW_H
