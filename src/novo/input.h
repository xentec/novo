#pragma once

#include "novo/global.h"
#include "novo/window.h"

#include <GLFW/glfw3.h>
#include <entityx/Event.h>

namespace novo {
namespace event {

using entityx::Event;

template<class Type>
struct Input : Event<Input<Type>> {};

struct Key : Input<Key>
{
	Key(i32 action, i32 key, i32 mod):	action(action), key(key), mod(mod) {}

	i32 action, key, mod;
};

struct Cursor : Input<Cursor>
{
	Cursor(f32 x, f32 y): x(x), y(y) {}

	f32 x, y;
};

struct Scroll : Input<Scroll>
{
	Scroll(f32 xoff, f32 yoff): offset { xoff, yoff } {}

	struct { f32 x, y; } offset;
};


template<class Type>
struct Window : Input<Window<Type>>
{
	Window(novo::Window& window): window(window) {}

	novo::Window& window;
};

namespace window
{
	struct Focus : Window<Focus>
	{
		Focus(novo::Window& window, bool focus): event::Window<Focus>(window), focus(focus) {}

		bool focus;
	};

	struct Size : Window<Size>
	{
		Size(novo::Window& window, i32 width, i32 height): event::Window<Size>(window), width(width), height(height) {}

		i32 width, height;
	};

	struct Attribute : Window<Attribute>
	{
		Attribute(novo::Window& window, novo::Window::Attribute attribute): event::Window<Attribute>(window), attribute(attribute){}

		novo::Window::Attribute attribute;
	};
}

}

struct InputManager: entityx::EventManager
{
public:
	InputManager(Window& window);
	virtual ~InputManager();

	void setup();

	void captureMouse(bool disable = true);
	void releaseMouse();

	static void poll();
private:
	Window& window;

	static void keyCB(GLFWwindow* gw, int key, int scancode, int action, int mod);
	static void mouseKeyCB(GLFWwindow* gw, int button, int action, int mod);
	static void mousePosCB(GLFWwindow* gw, double x, double y);
	static void mouseScrollCB(GLFWwindow* gw, double xoff, double yoff);

	static void winSizeCB(GLFWwindow* gw, int width, int height);
	static void winFocusCB(GLFWwindow* gw, int flag);
};

}
