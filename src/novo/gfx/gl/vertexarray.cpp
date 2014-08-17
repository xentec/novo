#include "vertexarray.h"

using namespace novo::gl;

VertexArray::VertexArray():
	Bindable(glGenVertexArrays,
			 glDeleteVertexArrays,
			 glBindVertexArray)
{
}

void VertexArray::bindAttribute(const Buffer& vbo, Attribute attrib, GLuint component_count, GLenum data_type, GLuint stride, GLuint offset, bool normalize)
{
	bind();
	vbo.bind();
	glVertexAttribPointer(attrib, component_count, data_type, static_cast<GLboolean>(normalize), stride, reinterpret_cast<void*>(offset));
	glEnableVertexAttribArray(attrib);
}

void VertexArray::unbind(Attribute attrib)
{
	glDisableVertexAttribArray(attrib);
}
