#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <novo/gfx/camera.h>
#include <novo/gfx/gl/obj.h>
#include <novo/gfx/gl/buffer.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace novo {
namespace graphics {

using namespace gl;

class Drawable
{
protected:
	GLuint vao;
	GLint prog;
	Buffer vbo, ibo;
public:
	Drawable():
		vbo(Buffer(Buffer::Vertex)), ibo(Buffer(Buffer::Index))
	{
		glGenVertexArrays(1, &vao);
	}
	virtual ~Drawable() {
		glDeleteVertexArrays(1, &vao);
	}

	virtual void draw(mat4* transform) = 0;
	GLint getProgram() const { return prog; }
};

}}

#endif // DRAWABLE_H
