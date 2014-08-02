#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <novo/gfx/camera.h>
#include <novo/gfx/gl/obj.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace novo {
namespace graphics {

class Drawable
{
protected:
	GLuint vao, vbo, ibo;
	GLint prog;
public:
	Drawable()  {
		glGenVertexArrays(1, &vao);
		util::createBuffers({&vbo, &ibo});
	}
	virtual ~Drawable() {
		util::destroyBuffers({vbo, ibo});
		glDeleteVertexArrays(1, &vao);
	}

	virtual void draw(mat4* transform) = 0;
	GLint getProgram() const { return prog; }
};

}}

#endif // DRAWABLE_H
