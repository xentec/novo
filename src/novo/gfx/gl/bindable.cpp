#include "bindable.h"

using namespace gl;

Bindable::Bindable(ObjType obj_type, GenFunc gen, DelFunc del, BindFunc bind, GLenum sub_type):
	Object(glGen(gen)),
	type(obj_type), subType(sub_type),
	glDelete(del), glBind(bind), glBindS(nullptr)
{}

Bindable::Bindable(ObjType obj_type, GenFunc gen, DelFunc del, BindFuncS bind):
	Object(glGen(gen)),
	type(obj_type),
	glDelete(del), glBind(nullptr), glBindS(bind)
{}

Bindable::~Bindable()
{
	glDelete(1, &id);
}


void Bindable::bind()
{
	if(glBind)
		glBind(subType, id);
	else
		glBindS(id);
}

GLuint Bindable::glGen(Bindable::GenFunc glGen) {
	GLuint id;
	glGen(1, &id);
	return id;
}
