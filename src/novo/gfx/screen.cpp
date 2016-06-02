#include "screen.h"

#include "novo/gfx/camera.h"
#include "novo/io/file.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <array>

using namespace novo::gfx;
using namespace novo::gl;
using namespace novo::gl::glb;
using namespace glm;

/*
	-1,-1 ---------- 1,-1
	  |  \            |
	  |      0,0      |
	  |            \  |
	-1,1 ----------- 1,1
*/

struct ScreenVertex
{
	vec2 pos, tex;
};

static const std::array<ScreenVertex, 2*3> vertices = {{
	{{-1, -1}, {0, 0}},
	{{-1,  1}, {0, 1}},
	{{ 1,  1}, {1, 1}},

	{{ 1,  1}, {1, 1}},
	{{ 1, -1}, {1, 0}},
	{{-1, -1}, {0, 0}}
}};


Screen::Screen(i32 width, i32 height, f32 fov, f32 near, f32 far, Framebuffer fb):
	Drawable(), Renderer(),
	vbo(BufferType::Data, "screen.vbo"),
	vao("screen.vao"),
	fb(fb),
	cbo(TextureType::S2D, "screen.cbo"),
	rbo("screen.rbo"),
	shader("screen"),
	aspect(static_cast<f32>(width)/height)
{
	if(fb.getLabel().empty())
		fb.setLabel("screen");

	// Upload the vertices
	vbo.setElements(BufferUsage::StaticDraw, vertices);

	vao.bindAttribute(vbo, 0, vertices[0].pos.length(), Data::Float, sizeof(ScreenVertex));
	vao.bindAttribute(vbo, 1, vertices[0].pos.length(), Data::Float, sizeof(ScreenVertex), sizeof(vertices[0].pos));

	shader.compile();
	shader["fb"] = 0;

	resize(width, height); // Initialize texture and renderbuffer
	setProjection(fov, near, far);

	fb.bind();

	fb.attach(0, cbo);
	fb.attach(GL_DEPTH_STENCIL_ATTACHMENT, rbo);
}

Screen::~Screen()
{
	fb.unbind();
}

void Screen::resize(i32 width, i32 height)
{
	glViewport(0, 0, width, height);

	cbo.setData(0, GL_RGB, width, height, 0, GL_RGB, Data::UByte, nullptr);
	rbo.store(GL_DEPTH24_STENCIL8, width, height);

	proj[0][0] *= aspect;
	aspect = static_cast<f32>(width)/height;
	proj[0][0] /= aspect;
}

void Screen::setProjection(f32 fov, f32 near, f32 far)
{
	proj = (far > 0) ? glm::perspective(glm::radians(fov), aspect, near, far) :
					   glm::infinitePerspective(glm::radians(fov), aspect, near);
}

void Screen::setView(const vec3& pos, const glm::quat& rot)
{
	static const vec3 up {0.f, 1.f, 0.f};
	static const vec3 fwd {0.f, 0.f, 1.f};
	view = glm::lookAt(pos, pos + rot * fwd, rot * up);
}

void Screen::clear(vec4 color)
{
	fb.bind();
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::update(Shader& shader) const
{
	shader["view"] = view;
	shader["proj"] = proj;
}

void Screen::use()
{
	fb.bind();
}

void Screen::draw(Shader*)
{
	using namespace gl::glb;

	fb.unbind();
	cbo.activate();
	cbo.bind();
	shader.use();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gl::disable(GL_CULL_FACE);
	gl::disable(GL_DEPTH_TEST);

	vao.drawArrays(GL_TRIANGLES, vertices.size());
}

void Screen::render(Drawable* obj, Shader* shader)
{
	fb.bind();
	obj->draw(shader);
}
