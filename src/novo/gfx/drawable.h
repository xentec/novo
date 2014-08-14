#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <novo/gfx/camera.h>
#include <novo/gfx/gl/vertexarray.h>
#include <novo/gfx/gl/buffer.h>
#include <novo/gfx/gl/program.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace novo {
namespace graphics {

using namespace gl;

struct DrawElementsIndrectCommand {
	GLuint
		count,
		instanceCount,
		firstIndex,
		baseVertex,
		baseInstance;
};

class Drawable
{
protected:
	VertexArray vao;
	Program prog;
	Buffer vbo, ibo;
public:
	Drawable():
		vbo(Buffer(buffer::Vertex, buffer::StaticDraw)), ibo(Buffer(buffer::Index, buffer::StaticDraw))
	{}

	virtual void draw(mat4* transform) = 0;
	Program getProgram() const { return prog; }
};

}}

#endif // DRAWABLE_H
