#ifndef TTGL_H
#define TTGL_H

#include <novo/global.h>
#include <novo/gfx/framebuffer.h>
#include <novo/gfx/window.h>

#include <boost/program_options.hpp>
#include <boost/circular_buffer.hpp>

#include <functional>
#include <deque>

#define APPNAME "Novo"
#define VERSION "0.0.1"


namespace novo {

using boost::program_options::variables_map;
using novo::graphics::Window;

class Novo
{
public:
	Novo(variables_map opts);
	virtual ~Novo();

	i32 run();
	void stop();

	sptr<Window> getMainWindow() const { return window; }
private:
	sptr<Window> window;
	sptr<graphics::Framebuffer> screen;
	bool noError;

	void onFocus(bool state);
	void onKey(i32 key, i32 scancode, i32 action, i32 mod);
	void onMouseButton(i32 key, i32 action, i32 mod);

	struct Connections {
		boost::signals2::connection key, mouse, mouseBTN, focus;
	} con;
	struct CachedBindings {
		std::function<Window::onCursorMoveSIG::signature_type> mouse;
	} func;

	boost::circular_buffer<string> lastGLCalls;

	static void glfwErrorCB(int code, const char* msg);
	static void glDebugCB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};

}

#endif // TTGL_H
