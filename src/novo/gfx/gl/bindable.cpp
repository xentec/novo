#include "bindable.h"

using namespace novo::gl;

GLenum Bindable::getType() const
{
	return type;
}

Bindable::Bindable(GenFuncN gen, DelFuncN del, BindFunc bind, GLenum sub_type, const string& label):
	Object(glGen(gen), std::bind(del, 1, std::placeholders::_1), label),
	type(sub_type),
	bind(std::bind(bind, sub_type, id))
{}

Bindable::Bindable(GenFuncN gen, DelFuncN del, BindFuncS bind, const string& label):
	Object(glGen(gen), std::bind(del, 1, std::placeholders::_1), label),
	bind(std::bind(bind, id))
{}

GLuint Bindable::glGen(Bindable::GenFuncN glGen) {
	GLuint id = 0;
	glGen(1, &id);
	return id;
}
