#include "vertexarray.h"

using namespace novo::gl;
using namespace glb;

VertexArray::VertexArray(const string& label):
	Bindable(GLenum::GL_VERTEX_ARRAY /* irrelevant */, label)
{
}

void VertexArray::use(const Buffer& buffer)
{
	bind();
	buffer.bind();
}

void VertexArray::bindAttribute(const Buffer& vbo, i32 attrib, u32 component_count, Data::Type data_type, u32 stride, u32 offset, bool normalize)
{
	if(vbo.getType() != BufferType::Vertex)
		throw OpenGLException(this, vbo.getLabel() + string(" not vertex buffer"));

	if(stride == 0)
		stride = component_count * Data::sizeOf(data_type);

	bind();

	glBindVertexBuffer(attrib, vbo, offset, stride);
	glVertexAttribBinding(attrib, attrib);
	glVertexAttribFormat(attrib, component_count, data_type, static_cast<GLboolean>(normalize), 0);

	//glVertexAttribPointer(attrib, component_count, data_type, static_cast<GLboolean>(normalize), stride, reinterpret_cast<void*>(offset) );

	glEnableVertexAttribArray(attrib);
}

void VertexArray::unbindAttrib(i32 attrib)
{
	glDisableVertexAttribArray(attrib);
}

void VertexArray::drawArrays(GLenum type, usz count)
{
	bind();
	glb::glDrawArrays(type, 0, count);
}

void VertexArray::drawElements(GLenum type, usz count, Data::Type data_type)
{
	bind();
	glb::glDrawElements(type, count, data_type, nullptr);
}
