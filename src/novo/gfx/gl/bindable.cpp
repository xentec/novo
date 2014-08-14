#include "bindable.h"

using namespace novo::gl;

Bindable::Bindable(GenFuncN gen, DelFuncN del, BindFunc bind, GLenum sub_type):
	Object(glGen(gen), std::bind(del, 1, std::placeholders::_1)),
	type(sub_type),
	glDelete(del), glBind(bind), glBindS(nullptr)
{}

Bindable::Bindable(GenFuncN gen, DelFuncN del, BindFuncS bind):
	Object(glGen(gen), std::bind(del, 1, std::placeholders::_1)),
	glDelete(del), glBind(nullptr), glBindS(bind)
{}

void Bindable::bind()
{
	if(glBind)
		glBind(type, id);
	else
		glBindS(id);
}

GLuint Bindable::glGen(Bindable::GenFuncN glGen) {
	GLuint id;
	glGen(1, &id);
	return id;
}
