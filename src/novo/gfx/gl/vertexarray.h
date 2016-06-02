#pragma once

#include "bindable.h"
#include "buffer.h"

namespace novo {
namespace gl {

struct VertexArray : Bindable<glb::GL_VERTEX_ARRAY, glb::glGenVertexArrays, glb::glDeleteVertexArrays, dtl::bindFunc<glb::glBindVertexArray>>
{
	VertexArray(const string& label = "");

	void use(const Buffer& buffer);

	void bindAttribute(const Buffer& vbo, i32 attrib, u32 component_count, Data::Type data_type, u32 stride = 0, u32 offset = 0, bool normalize = false);

	template<class T>
	void addAttribute(Buffer& vbo, i32 attrib, const T& data, u32 component_count, Data::Type data_type, u32 stride = 0, bool normalize = false)
	{
		bindAttribute(vbo, attrib, component_count, data_type, stride, vbo.offset(), normalize);
		vbo.addSubElements(data);
	}

	void unbindAttrib(i32 attrib);

	void drawArrays(glb::GLenum type, usz count);
	void drawElements(glb::GLenum type, usz count, Data::Type data_type);
};

}}
