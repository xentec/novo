#include "object.h"

using namespace novo::gl;

Object::Object(GLuint gl_id, DelFunc func, const string& label):
	id(gl_id), label(label), glDel(func)
{
	refs.emplace(id, 1);
	DBG("GLObj ["<< id <<"] '" << label << "' created (" << refs[id] << ")")
}

Object::Object(GLuint gl_id, DelFuncP func, const string& label):
	Object(gl_id, [=](GLuint i){ func(&i); }, label)
{}

Object::Object(const Object& other):
	id(other.id), label(other.label), glDel(other.glDel)
{
	refs[id]++;
	DBG("GLObj ["<< id <<"] '" << label << "' copied (" << refs[id] << ")")
}

Object::~Object() {
	DBG("GLObj ["<< id <<"] '" << label << "' dtored (" << refs[id] << ")")
	if(--refs[id] == 0) {
		glDel(id);
		refs.erase(id);
		DBG("GLObj ["<< id <<"] '" << label << "' deleted (" << refs[id] << ")")
	}
}

std::unordered_map<GLuint, u32> Object::refs;
