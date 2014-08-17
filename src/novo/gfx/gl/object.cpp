#include "object.h"

using namespace novo::gl;

Object::Object(GLuint gl_id, DelFunc func):
	id(gl_id), label(""), glDel(func)
{
	refs.emplace(id, 1);
}

Object::Object(GLuint gl_id, DelFuncP func):
	Object(gl_id, [=](GLuint i){ func(&i); })
{}

Object::Object(const Object& other):
	id(other.id), label(other.label), glDel(other.glDel)
{
	refs[id]++;
}

Object::~Object() {
	if(--refs[id] == 0) {
		glDel(id);
		refs.erase(id);
	}
}

std::unordered_map<GLuint, u32> Object::refs;
