#include "buffer.h"

#include <novo/gfx/gl/names.h>

static GLuint glGenBuffer() {
	GLuint id;
	glGenBuffers(1, &id);
	return id;
}

namespace gl {

Buffer::Buffer(buffer::Type type):
	Buffer(type, glGenBuffer())
{}

Buffer::Buffer(buffer::Type type, GLuint id):
	Bindable(id, Bindable::ObjType::Buffer, glBindBuffer, type)
{}


Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
}

void Buffer::reserve(u32 bytes_size, buffer::Usage usage)
{
	setData(bytes_size, nullptr, usage);
}

void Buffer::setData(u32 bytes_size, const void *data, buffer::Usage usage)
{
	bind();
	glBufferData(subType, bytes_size, data, usage);
	buffer_size = bytes_size;
}


void Buffer::setSubData(u32 bytes_offset, u32 bytes_size, const void *data)
{
	bind();
	glBufferSubData(subType, bytes_offset, bytes_size, data);
}

u32 Buffer::size() {
	return buffer_size;
}

// static

std::vector<Buffer> Buffer::generate(buffer::Type type, u32 num, string prefix)
{
	std::vector<Buffer> buffs;
	std::vector<GLuint> ids(num);

	if(prefix.empty())
		prefix = gl::names::buffer[type];

	prefix.append(".");

	buffs.reserve(num);
	glGenBuffers(num, &*ids.begin());

	for(u32 i = 1; i <= num; i++) {
		Buffer b(type, ids[i]);
		b.setLabel(prefix + std::to_string(ids[i]));

		buffs.push_back(b);
	}
	return buffs;
}

}
