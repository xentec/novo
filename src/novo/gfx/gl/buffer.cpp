#include "buffer.h"

#include <novo/gfx/gl/names.h>

namespace gl {

Buffer::Buffer(buffer::Type type, buffer::Usage usage):
	Bindable(Bindable::Buffer, glGenBuffers, glDeleteBuffers, glBindBuffer, type),
	usage(usage), bufSize(0), bufOffset(0)
{}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
}

buffer::Usage Buffer::getUsage() const
{
	return usage;
}

void Buffer::setUsage(const buffer::Usage &value)
{
	usage = value;
}

void Buffer::allocate(u32 bytes_size)
{
	setData(bytes_size, nullptr);
}

void Buffer::setData(u32 bytes_size, const void *data)
{
	bind();
	glBufferData(subType, bytes_size, data, usage);
	bufSize = bytes_size;

	if(data != nullptr)
		bufOffset = bytes_size;
}


void Buffer::setSubData(u32 bytes_offset, u32 bytes_size, const void *data)
{
	bind();
	glBufferSubData(subType, bytes_offset, bytes_size, data);
}

void Buffer::addSubData(u32 bytes_size, const void* data)
{
	if(bufOffset + bytes_size > bufSize)
		return; // TODO: Error

	setSubData(bufOffset, bytes_size, data);
	bufOffset += bytes_size;
}

u32 Buffer::size() const {
	return bufSize;
}

u32 Buffer::offset() const {
	return bufOffset;
}

}
