#include "app.h"

//#include "novo/event.h"
#include "novo/world.h"
#include "novo/gfx/gl/names.h"
#include "novo/gfx/screen.h"
#include "novo/window.h"

#include "novo/system/control.h"
#include "novo/system/renderer.h"
#include "novo/component/controllable.h"
#include "novo/component/motion.h"
#include "novo/component/screen.h"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <entityx/Entity.h>
#include <glbinding/Binding.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <iostream>
#include <thread>

namespace novo {
using namespace gl;
using namespace component;

using namespace std::chrono;
using namespace std::placeholders;

using std::string;
using std::bind;

using entityx::Entity;

static const string fmtTitle(APPNAME " - MSPF: {:.4f}ms ::S: {}");
static const struct Size { i32 width, height; } winSize { 1980, 1080 };

static void glfwErrorCB(int code, const char* msg);
static void glDebugCB(glb::GLenum source, glb::GLenum type, glb::GLuint id, glb::GLenum severity, glb::GLsizei length, const glb::GLchar* message, const void* userParam);

App* App::instance = nullptr;

App::App():
	running(true),
	window(winSize.width, winSize.height, APPNAME),
	input(window),
	worlds{}
{
	if(instance)
		throw Exception("Only one novo::App instance allowed");
	instance = this;

	// GLFW
	glfwSetErrorCallback(glfwErrorCB);
	if(!glfwInit())
		throw Exception("GLFW init failed");

	// OpenGL / GLBinding
	Window test(1, 1, APPNAME " - GL Test");
	test.setup.visible = false;
	test.setup.debugging = true;
	test.open();
	test.bindContext();

	glbinding::Binding::initialize(glfwGetProcAddress);

	window.setup.visible = false;
	window.setup.resizable = true;
	window.setup.GLversion.major = 4;
	window.setup.GLversion.minor = 5;
	window.setup.GLprofile = window::Config::Profile::CORE;
	window.setup.debugging = true;
}

App::~App()
{
	window.close();
	glfwTerminate();
	instance = nullptr;
}

App& App::getMe()
{
	return *instance;
}

i32 App::run()
{
	window.open();
	window.bindContext();
	window.setVsync(false);

	input.setup();
	input.subscribe<event::Key>(*this);
	input.subscribe<event::window::Focus>(*this);

	input.captureMouse();

	gl::enable(glb::GL_DEBUG_OUTPUT);
	gl::enable(glb::GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glb::glDebugMessageCallback(&glDebugCB, this);
	debug::messageControl({debug::Source::API, debug::Type::Other, 131185, false});

	///##################################
	///##################################

	gfx::Screen screen(winSize.width, winSize.height);

	auto renderer = std::make_shared<system::Renderer>();
	auto control = std::make_shared<system::PlayerControl>();

	renderer->addShader(gfx::Shader("cube"));
	gfx::Shader shaderNormals("normals");
	shaderNormals.setPolyMode(gl::glb::GL_LINE);
//	renderer->addShader(shaderNormals);

	u32 size = 8;

	World world(size*size);
	world.systems.add(renderer);
	world.systems.add(control);
	world.systems.configure();

	input.subscribe<event::Key>(*control);
	input.subscribe<event::Cursor>(*control);

	Entity player = world.entities.create();
	player.assign<Position>(glm::vec3(0,0,1));
	player.assign<Motion>();
	player.assign<Controllable>();
	player.assign<Screen>(&screen);

	worlds.emplace("1", &world);

	///##################################
	///##################################

	// Debug
	Query samples(QueryType::SamplesPassed, "sample");

	struct {
		steady_clock::time_point now, then, title;
		duration<entityx::TimeDelta, std::milli> elapsed { 0 }, lag { 0 };
		const duration<entityx::TimeDelta, std::milli> target { 1000.f/60.f };
	} time;

	time.then = time.title = steady_clock::now();
	i32 totalFrames = 0;

	window.show();

	while(running)
	{
		time.now = steady_clock::now();		  // new
		time.elapsed = time.now - time.then;  // delta

		time.then = time.now;		// replace old with new time
		time.lag += time.elapsed;	// add delta time to lag

		input.poll();

		if(!window.isOpen())
			break;

		/// Update ##########################
		while(time.lag >= time.target) { // compensate lost frames
			for(auto world: worlds) {
				world.second->update(1.0);
			}
			time.lag -= time.target;
		}

		/// Render ##########################
		screen.clear();

		samples.begin();

		for(auto world: worlds)
			world.second->render(time.lag / time.target);

		samples.end();

		screen.draw();
		///##################################
		window.present();

		totalFrames++; // +1 Frame
		if(duration_cast<seconds>(steady_clock::now() - time.title).count())
		{
			window.setTitle(fmt::format(fmtTitle, time.elapsed.count(), samples.get<u32>(QueryParameter::Result)));

			totalFrames = 0;
			time.title = steady_clock::now();
		}
		std::cout.flush();

//		if(time.elapsed < time.target)
//			std::this_thread::sleep_for(time.target - time.elapsed);

	}

	return 0;
}

void App::stop() {
	running = false;
}

Window& App::getWindow()
{
	return window;
}

void App::receive(const event::Key& ev)
{
	switch(ev.action)
	{
	case GLFW_PRESS:
		switch(ev.key)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			if(window.getCursorMode() == Window::CursorMode::NORMAL)
				input.captureMouse();

			break;
		case GLFW_KEY_ESCAPE:
			if(window.getCursorMode() != Window::CursorMode::NORMAL)
				input.releaseMouse();
			else
				stop();

			break;
		case GLFW_KEY_TAB:
			static u32 e;
			if(++e > 5) e = 0;
//			screen->getProgram().setUniform("effectFlag", e);
			break;

		}
		break;
	}
}

void App::receive(const event::window::Focus& ev) {
	if(!ev.focus)
		input.releaseMouse();
}


/*


void Novo::onScroll(f64 x, f64 y) {
	sptr<Camera> cam = screen->getCamera();

	cam->setNearPlane(cam->getNearPlane() + static_cast<f32>(x));
	cam->setFarPlane(cam->getFarPlane() + static_cast<f32>(y));
}
*/



void glfwErrorCB(int code, const char* msg)
{
	fmt::print(stderr, "glfw: {}: {}\n", code, msg);
}


void glDebugCB(glb::GLenum source, glb::GLenum type, glb::GLuint id, glb::GLenum severity, glb::GLsizei length, const glb::GLchar* message, const void* userParam)
{
	using namespace novo::gl;

	string crit = severity == novo::gl::debug::Severity::High ? ":!" : "";
	string out = fmt::format("GL{}: {}::{}::{}::{}: {}\n", crit, id, names::debug.at(source), names::debug.at(type), names::debug.at(severity), message);

	if(severity == novo::gl::debug::Severity::High)
	{
		fmt::print(std::cerr, out);
		App* novo = reinterpret_cast<App*>(const_cast<void*>(userParam));
		novo->stop(); // TODO: work around const violation

//		throw NovoException(out); // TODO: work around throwing exceptions in C
	} else
	{
		fmt::print(out);
	}
}

}
