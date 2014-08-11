#include "buffer.h"

#include "names.h"

static GLuint glGenBuffer() {
	GLuint id;
	glGenBuffers(1, &id);
	return id;
}

namespace gl {

Buffer::Buffer(Buffer::Type type, string name):
	Buffer(type, name, glGenBuffer()) {}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
}

void Buffer::bind()
{
	glBindBuffer(type, id);
}

std::vector<Buffer> Buffer::generate(Buffer::Type type, u32 num, string prefix)
{
	std::vector<Buffer> buffs;
	std::vector<GLuint> ids(num);

	if(prefix.empty())
		prefix = gl::names::buffer[type];

	prefix.append(".");

	buffs.reserve(num);
	glGenBuffers(num, &*ids.begin());

	for(u32 i = 1; i <= num; i++) {
		buffs.push_back(Buffer(type, prefix + std::to_string(ids[i]), ids[i]));
	}
	return buffs;
}

Buffer::Buffer(Buffer::Type t, const string& name, GLuint id):
	Object(id, name),
	type(t)
{}

}
