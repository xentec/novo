#include "bindable.h"

using namespace gl;

Bindable::Bindable(GLuint id, ObjType obj_type, BindFunc bind, GLenum sub_type):
	Object(id),
	type(obj_type), glBind(bind), glBindS(nullptr), subType(sub_type)
{}

Bindable::Bindable(GLuint id, ObjType obj_type, BindFuncS bind):
	Object(id),
	type(obj_type), glBind(nullptr), glBindS(bind)
{}

void Bindable::bind()
{
	if(bindings.count(type) == 0) {
		bindings.emplace(type, id);
	} else {
		if(bindings[type] == id)
			return;

		bindings[type] = id;
	}

	if(glBind)
		glBind(subType, id);
	else
		glBindS(id);
}

std::unordered_map<GLenum, GLuint> Bindable::bindings;
