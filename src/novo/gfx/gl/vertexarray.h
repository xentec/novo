#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "bindable.h"
#include "buffer.h"
#include "program.h"

namespace novo {
namespace gl {

class VertexArray : public Bindable
{
public:
	VertexArray();

	void bindAttribute(const Buffer& vbo, Attribute attrib, GLuint component_count, GLenum data_type, GLuint stride = 0, GLuint offset = 0, bool normalize = false);
	void unbind(Attribute attrib);

	template<typename T>
	void addAttribute(Buffer& vbo, const T& data, Attribute attrib, GLuint component_count, GLenum data_type, GLuint stride = 0, bool normalize = false)
	{
		bindAttribute(vbo, attrib, component_count, data_type, stride, vbo.offset(), normalize);
		vbo.addSubElements(data);
	}

};

}}

#endif // VERTEXARRAY_H
