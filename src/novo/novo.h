#ifndef TTGL_H
#define TTGL_H

#include <novo/global.h>
#include <novo/gfx/framebuffer.h>
#include <novo/gfx/window.h>

#include <functional>
#include <boost/program_options.hpp>

#define APPNAME "Novo"
#define VERSION "0.0.1"

using boost::program_options::variables_map;

using namespace novo;
using novo::graphics::Window;

class Novo
{
public:
	Novo(variables_map opts);
	virtual ~Novo();

	i32 run();

	inline sptr<Window> getMainWindow() const { return window; }
private:
	sptr<Window> window;
	sptr<graphics::Framebuffer> screen;

	void onFocus(bool state);
	void onKey(i32 key, i32 scancode, i32 action, i32 mod);
	void onMouseButton(i32 key, i32 action, i32 mod);

	struct Connections {
		boost::signals2::connection key, mouse, mouseBTN, focus;
	} con;
	struct CachedBindings {
		std::function<Window::onCursorMoveSIG::signature_type> mouse;
	} func;
};

#endif // TTGL_H
