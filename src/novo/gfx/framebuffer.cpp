#include "framebuffer.h"


#include <novo/gfx/gl/obj.h>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

using namespace novo::graphics;

static const GLfloat fbVertices[(2*3)*2] = {
	-1, -1,  -1,  1,   1,  1, // Left
	 1,  1,   1, -1,  -1, -1, // Right
};

static const GLfloat fbTex[(2*3)*2] = {
	0, 0,  0, 1,  1, 1,
	1, 1,  1, 0,  0, 0,
};

Framebuffer::Framebuffer(i32 width, i32 height, sptr<Camera> camera, bool bind_now):
	Drawable(), Renderer(),
	cam(camera)
{
	size_t vxSize = sizeof(fbVertices);
	size_t txSize = sizeof(fbTex);

	// Create vertex buffes to hold our vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Upload the vertices
	glBufferData(GL_ARRAY_BUFFER, vxSize + txSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vxSize, &fbVertices);
	glBufferSubData(GL_ARRAY_BUFFER, vxSize, txSize, &fbTex);

	glBindVertexArray(vao);

	// Program
	prog = util::createProgramFromFiles("screen.v.glsl", "screen.f.glsl");
	glUseProgram(prog);
	glUniform1i(glGetUniformLocation(prog, "fb"), 0);

	{
		GLint posAttrib = glGetAttribLocation(prog, "pos");
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(posAttrib);

		GLint texAttrib = glGetAttribLocation(prog, "tex");
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(vxSize));
		glEnableVertexAttribArray(texAttrib);
	}

	glGenTextures(1, &cb);
	glGenRenderbuffers(1, &rbo);
	glGenFramebuffers(1, &fb);

	resize(width, height); // Initialize texture and renderbuffer

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

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
	glDeleteProgram(prog);
	glDeleteTextures(1, &cb);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
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
				 0, GL_RGB,
				 width, height,
				 0, GL_RGB,
				 GL_UNSIGNED_BYTE, nullptr);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void Framebuffer::draw(mat4*)
{
	unbind();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cb);
	glUseProgram(prog);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Framebuffer::render(Drawable* obj)
{
	bind();
	glUseProgram(obj->getProgram());
	glUniformMatrix4fv(glGetUniformLocation(obj->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(cam->getView()));
	glUniformMatrix4fv(glGetUniformLocation(obj->getProgram(), "proj"), 1, GL_FALSE, glm::value_ptr(cam->getProjection()));
	mat4 model;
	obj->draw(&model);
}

sptr<Camera> Framebuffer::getCamera()
{
	return cam;
}
