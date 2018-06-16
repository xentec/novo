#pragma once

#include "novo/global.h"
#include "novo/exception.h"
#include "novo/input.h"

#include <entityx/Event.h>

#include <queue>
#include <unordered_map>

#define APPNAME "Novo"
#define VERSION "0.2.0"

namespace novo {

using entityx::Receiver;

struct Window;
struct World;

struct App : Receiver<App>
{
public:
	App();
	virtual ~App();

	static App& getMe();

	i32 run();
	void stop();

	Window& getWindow();

	void receive(const event::Key& ev);
	void receive(const event::window::Focus& ev);
private:
	static App* instance;

	bool running;
	Window window;
	InputManager input;

	std::unordered_map<string, World*> worlds;
};

}
