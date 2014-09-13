#include "buffer.h"

#include <novo/gfx/gl/names.h>

using namespace novo::gl;

Buffer::Buffer(GLenum type, const string& label):
	Bindable<GL_BUFFER, glGenBuffers, glDeleteBuffers, glBindBuffer>(type, label),
	usage(GL_BUFFER), bufSize(0), bufOffset(0)
{}

GLenum Buffer::getUsage() const
{
	return usage;
}

void Buffer::allocate(GLenum usage, u32 bytes_size)
{
	setData(usage, bytes_size, nullptr);
}

void Buffer::setData(GLenum usage, u32 bytes_size, const void *data)
{
	if(usage == GL_BUFFER)
		throw OpenGLException(this, "no buffer usage set");

	bind();
	glBufferData(type, bytes_size, data, usage);
	bufSize = bytes_size;
	this->usage = usage;

	if(data != nullptr)
		bufOffset = bytes_size;
}


void Buffer::setSubData(u32 bytes_offset, u32 bytes_size, const void *data)
{
	bind();
	glBufferSubData(type, bytes_offset, bytes_size, data);
}

void Buffer::addSubData(u32 bytes_size, const void* data)
{
	if(bufOffset + bytes_size > bufSize)
		return; // TODO: Error

	setSubData(bufOffset, bytes_size, data);
	bufOffset += bytes_size;
}

const void* Buffer::map(GLenum access)
{
	bind();
	return glMapBuffer(type, access);
}

const void* Buffer::mapRange(u32 bytes_size, u32 offset, BufferAccessMask access)
{
	bind();
	return glMapBufferRange(type, offset, bytes_size, access);
}

u32 Buffer::size() const {
	return bufSize;
}

u32 Buffer::offset() const {
	return bufOffset;
}
