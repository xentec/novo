#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <novo/gfx/camera.h>
#include <novo/gfx/gl/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace novo::gl;

namespace novo {
namespace graphics {

class Drawable
{
protected:
	VertexArray vao;
	Buffer vbo, ibo;
	Program prog;
public:
	Drawable(const string& name = ""):
		vbo(Buffer(BufferType::Vertex, name+".vbo")),
		ibo(Buffer(BufferType::Index,  name+".ibo")),
		vao(VertexArray(name+".vao")),
		prog(Program(name+".prog"))
	{}

	virtual void draw(mat4* transform) = 0;
	Program getProgram() { return prog; }
};

}}

#endif // DRAWABLE_H
