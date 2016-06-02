#include "buffer.h"

#include "debug.h"
#include "names.h"

using namespace novo::gl;
using namespace glb;

Buffer::Buffer(Type type, const string& label):
	Bindable<GL_BUFFER, glGenBuffers, glDeleteBuffers, glBindBuffer>(type, label),
	usage(GL_BUFFER), bufSize(0), bufOffset(0)
{}

Buffer::Usage Buffer::getUsage() const
{
	return usage;
}

void Buffer::allocate(Usage usage, usz bytes_size)
{
	setData(usage, bytes_size, nullptr);
}

void Buffer::setData(Usage buffer_usage, usz bytes_size, const void *data)
{
	bind();
	glBufferData(type, bytes_size, data, buffer_usage);
	bufSize = bytes_size;
	usage = buffer_usage;

	if(data != nullptr)
		bufOffset = bytes_size;
}

void Buffer::setSubData(usz bytes_offset, usz bytes_size, const void *data)
{
	bind();
	glBufferSubData(type, bytes_offset, bytes_size, data);
	bufOffset = bytes_offset + bytes_size;
}

void Buffer::addSubData(usz bytes_size, const void* data)
{
/*
	if(bufOffset + bytes_size > bufSize) {
		//TODO: better error handling?
		string msg = (dtl::excDbg % glbinding::Meta::getString(getGLType()) % getLabel() % "addSubData failed: offset > buffer size").str();
		glDebugMessageInsert(debug::Source::Application, debug::Type::Error, 200001, debug::Severity::Medium, msg.size(), msg.c_str());
		return;
	}
*/
	bind();
	glBufferSubData(type, bufOffset, bytes_size, data);
	bufOffset += bytes_size;
}

const void* Buffer::map(GLenum access)
{
	bind();
	return glMapBuffer(type, access);
}

const void* Buffer::mapRange(usz bytes_size, usz offset, BufferAccessMask access)
{
	bind();
	return glMapBufferRange(type, offset, bytes_size, access);
}

usz Buffer::size() const {
	return bufSize;
}

usz Buffer::offset() const {
	return bufOffset;
}
