#include "bindable.h"

using namespace novo::gl;

Bindable::Bindable(GenFunc gen, DelFunc del, BindFunc bind, GLenum sub_type):
	Object(glGen(gen)),
	type(sub_type),
	glDelete(del), glBind(bind), glBindS(nullptr)
{}

Bindable::Bindable(GenFunc gen, DelFunc del, BindFuncS bind):
	Object(glGen(gen)),
	glDelete(del), glBind(nullptr), glBindS(bind)
{}

Bindable::~Bindable()
{
	glDelete(1, &id);
}


void Bindable::bind()
{
	if(glBind)
		glBind(type, id);
	else
		glBindS(id);
}

GLuint Bindable::glGen(Bindable::GenFunc glGen) {
	GLuint id;
	glGen(1, &id);
	return id;
}
