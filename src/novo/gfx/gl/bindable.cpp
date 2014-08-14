#include "bindable.h"

using namespace novo::gl;

Bindable::Bindable(GenFuncN gen, DelFuncN del, BindFunc bind, GLenum sub_type):
	Object(glGen(gen), std::bind(del, 1, std::placeholders::_1)),
	type(sub_type),
	bind(std::bind(bind, sub_type, id))
{}

Bindable::Bindable(GenFuncN gen, DelFuncN del, BindFuncS bind):
	Object(glGen(gen), std::bind(del, 1, std::placeholders::_1)),
	bind(std::bind(bind, id))
{}

GLuint Bindable::glGen(Bindable::GenFuncN glGen) {
	GLuint id;
	glGen(1, &id);
	return id;
}
