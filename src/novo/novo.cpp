#include "novo.h"

#include <novo/io.h>
#include <novo/entities/randomcubes.h>
#include <novo/entities/origin.h>
#include <novo/gfx/gl/names.h>
#include <novo/gfx/framebuffer.h>
#include <novo/gfx/window.h>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/ptr_container/ptr_list.hpp>

#include <glbinding/Binding.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include <iostream>
#include <thread>

namespace novo {

using namespace graphics;

using namespace std::chrono;
using namespace std::placeholders;
using std::string;
using std::bind;

using boost::program_options::variables_map;
using boost::format;
using boost::ptr_list;

format fmtTitle(APPNAME" - FPS: %d ::S: %d");

Novo::Novo(variables_map opts):
	window(new Window(800, 600, APPNAME)),
	lastGLCalls(2),
	noError(true)
{
	// GLFW
	glfwSetErrorCallback(glfwErrorCB);
	if(!glfwInit())
		throw std::runtime_error(string("GLFW init failed!"));


	// OpenGL / GLEW
	Window test(1,1, APPNAME " - GL Test");
	test.config.visible = false;
	test.config.debuging = true;
	test.open();
	test.bindContext();

	glbinding::Binding::initialize(false);

	window->config.resizable = false;
	window->config.GLversion.major = 3;
	window->config.GLversion.minor = 2;
	window->config.GLprofile = WindowConfig::Profile::CORE;
	window->config.debuging = true;

	using glbinding::CallbackMask;

#if DEBUG > 2
	lastGLCalls.set_capacity(2);
	glbinding::setCallbackMask(CallbackMask::Before | CallbackMask::ParametersAndReturnValue);
	glbinding::setBeforeCallback([&](const glbinding::FunctionCall& call)
	{
		std::stringstream cerr;
		cerr << call.function.name() << "(";
		for (unsigned i = 0; i < call.parameters.size(); ++i)
		{
			cerr << call.parameters[i]->asString();
			if (i < call.parameters.size() - 1)
				cerr << ", ";
		}
		cerr << ")";
		if (call.returnValue)
			cerr << " -> " << call.returnValue->asString();

		cerr.flush();
		lastGLCalls.push_back(cerr.str());
	});
#endif
}

Novo::~Novo()
{
	glbinding::setCallbackMask(glbinding::CallbackMask::None);
	window->close();
	glfwTerminate();
}

void Novo::stop() {
	noError = false;
}

i32 Novo::run() {
	using namespace ::gl;

	window->open();
	window->bindContext();
	window->setVsync(false);


	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(&glDebugCB, this);
	debug::messageControl({debug::Source::API, debug::Type::Other, 131185, false});

	///##################################
	///##################################
	sptr<Camera> cam(new Camera(vec3(0), 800, 600));
	screen = sptr<Framebuffer>(new Framebuffer(800, 600, cam, false));

	ptr_list<Drawable> objs;

	u32 size = 64;
	objs.push_back(new RandomCubes(size*size, size*size, vec3(0)));
	objs.push_back(new Origin(size, 8.0));

	///##################################
	///##################################

	func.mouse = bind(&Camera::mouseCallback, screen->getCamera().get(), _1, _2);

	con.focus = window->onFocus.connect(bind(&Novo::onFocus, this, _1));
	con.key = window->onKey.connect(bind(&Novo::onKey, this, _1, _2, _3, _4));
	con.mouse = window->onCursorMove.connect(func.mouse);
	con.mouseBTN = window->onMouseButton.connect(bind(&Novo::onMouseButton, this, _1, _2, _3));

	// Debug
	GLuint query = 0;
	glGenQueries(1, &query);

	steady_clock::time_point tick = steady_clock::now();
	i32 totalFrames = 0;
	while(noError && window->isOpen()) {
		///##################################

		screen->getCamera()->moveUpdate(1);
		screen->bind();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBeginQuery(GL_SAMPLES_PASSED, query);

		///TODO glm::mat4_cast(glm::angleAxis(glm::sin((float)glfwGetTime()), vec3(0.0f, 0.0f, 1.0f)));

		for(Drawable& obj : objs)
			screen->render(&obj);

		glEndQuery(GL_SAMPLES_PASSED);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		screen->draw();

		///##################################
		window->present();
		window->poll();

		totalFrames++; // +1 Frame
		if(duration_cast<seconds>(steady_clock::now() - tick).count()) {

			GLuint samples;
			glGetQueryObjectuiv(query, GL_QUERY_RESULT, &samples);

			fmtTitle % totalFrames % samples;
			window->setTitle(fmtTitle.str());

			totalFrames = 0;
			tick = steady_clock::now();
		}
		//TODO: main loop sleep
	}

	return 0;
}

void Novo::onFocus(bool state) {
	if(!state) {
		con.mouse.disconnect();
		window->setCursorMode(CursorMode::NORMAL);
	}
}

void Novo::onMouseButton(i32 key, i32 action, i32 mod) {
	if(action == GLFW_PRESS && window->onCursorMove.empty()) {
		con.mouse = window->onCursorMove.connect(func.mouse);
		window->setCursorMode(CursorMode::DISABLED);
		return;
	}
}

void Novo::onKey(i32 key, i32 scancode, i32 action, i32 mod) {
	sptr<Camera> cam = screen->getCamera();
	vec3 camVal = cam->getVelocity();

		switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_W:
					camVal.z++;
					break;
				case GLFW_KEY_S:
					camVal.z--;
					break;
				case GLFW_KEY_D:
					camVal.x--;
					break;
				case GLFW_KEY_A:
					camVal.x++;
					break;
				case GLFW_KEY_SPACE:
					camVal.y++;
					break;
				case GLFW_KEY_C:
					camVal.y--;
					break;
				case GLFW_KEY_ESCAPE:
					if(!con.mouse.connected())
						window->close();
					else {
						con.mouse.disconnect();
						window->setCursorMode(CursorMode::NORMAL);
					}
					return;

				case GLFW_KEY_TAB:
					static int e;
					if(++e > 5) e = 0;
					screen->getProgram().setUniform("effectFlag", e);
					break;

			}
			break;
		case GLFW_RELEASE:
			switch(key) {
				case GLFW_KEY_W:
					camVal.z--;
					break;
				case GLFW_KEY_S:
					camVal.z++;
					break;
				case GLFW_KEY_D:
					camVal.x++;
					break;
				case GLFW_KEY_A:
					camVal.x--;
					break;
				case GLFW_KEY_SPACE:
					camVal.y--;
					break;
				case GLFW_KEY_C:
					camVal.y++;
					break;
			}
			break;
	}
	cam->setVelocity(camVal);
}


void Novo::glfwErrorCB(int code, const char* msg)
{
	std::cerr << "[glfw]: " << code << ": " << msg << std::endl;
	std::cerr.flush();
}

void Novo::glDebugCB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void *userParam)
{
#define out std::cout
	using std::endl;
	using namespace novo::gl::names;

	static format err("GL%s: %d::%s::%s::%s: %s\n");

	string crit = severity == gl::debug::Severity::High ? ":!" : "";

	out << (err % crit % id % debug[source] % debug[type] % debug[severity] % message);

	if(severity == GL_DEBUG_SEVERITY_HIGH) {
		const Novo* novo = reinterpret_cast<const Novo*>(userParam);
		const_cast<Novo*>(novo)->stop(); // TODO: work around const violation
#if DEBUG > 2
		out << "{" << std::endl;
		for(auto& call : novo->lastGLCalls) {
			out << "\t" << call << std::endl;
		}
		out << "}" << std::endl;
#endif
	}


	out.flush();
#undef out
	/*
	cerr << "Stack trace:" << endl;
	cerr << saneStackTrace() << endl;
	cerr.flush();
	*/

}

}
