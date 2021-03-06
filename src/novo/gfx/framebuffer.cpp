#include "framebuffer.h"

#include <glm/gtc/type_ptr.hpp>

#include <array>

using namespace novo::graphics;

static const std::array<f32, (2*3)*2> fbVertices = {
	-1, -1,  -1,  1,   1,  1, // Left
	 1,  1,   1, -1,  -1, -1, // Right
};

static const std::array<f32, (2*3)*2> fbTex = {
	0, 0,  0, 1,  1, 1,
	1, 1,  1, 0,  0, 0,
};

Framebuffer::Framebuffer(i32 width, i32 height, sptr<Camera> camera, bool bind_now):
	Drawable("FB"), Renderer(),
	cam(camera)
{
	// Program
	prog.attach(Shader::load(ShaderType::Vertex, "screen.v.glsl", true, "FB.prog.vrtx"));
	prog.attach(Shader::load(ShaderType::Fragment, "screen.f.glsl", true, "FB.prog.frag"));
	prog.bindFragDataLocation(0, "color");
	prog.use();

	// Upload the vertices
	vbo.allocateElements(BufferUsage::StaticDraw, fbVertices, fbTex);

	vao.addAttribute(vbo, fbVertices, prog.getAttribute("pos"), 2, DataType::Float);
	vao.addAttribute(vbo, fbTex, prog.getAttribute("tex"), 2, DataType::Float);

	prog.setUniform("fb", 0);

	glGenTextures(1, &cb);
	glGenRenderbuffers(1, &rbo);
	glGenFramebuffers(1, &fb);

	resize(width, height); // Initialize texture and renderbuffer

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(GL_CLAMP_TO_BORDER));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(GL_CLAMP_TO_BORDER));

	bind();

	glFramebufferTexture2D(GL_FRAMEBUFFER,
						   GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D, cb, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,
							  GL_DEPTH_STENCIL_ATTACHMENT,
							  GL_RENDERBUFFER, rbo);
	if(!bind_now) unbind();
}

Framebuffer::~Framebuffer()
{
	unbind();
	glDeleteFramebuffers(1, &fb);
	glDeleteTextures(1, &cb);
	glDeleteRenderbuffers(1, &rbo);
}

void Framebuffer::bind()
{
	//if(bound) return; // TODO: Check other binds
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	bound = true;
}

void Framebuffer::unbind()
{
	//if(!bound) return;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	bound = false;
}

void Framebuffer::resize(i32 width, i32 height)
{
	cam->resize(width, height);
	glViewport(0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, cb);
	glTexImage2D(GL_TEXTURE_2D,
				 0, static_cast<int>(GL_RGB),
				 width, height,
				 0, GL_RGB,
				 GL_UNSIGNED_BYTE, nullptr);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void Framebuffer::draw(mat4*)
{
	unbind();
	vao.bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cb);
	prog.use();

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Framebuffer::render(Drawable* obj)
{
	bind();
	Program p = obj->getProgram();
	p.use();
	p.setUniform("view", cam->getView());
	p.setUniform("proj", cam->getProjection());

	mat4 model;
	obj->draw(&model);
}

sptr<Camera> Framebuffer::getCamera()
{
	return cam;
}
