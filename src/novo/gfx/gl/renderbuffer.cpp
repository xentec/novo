#include "renderbuffer.h"

using namespace novo::gl;
using namespace glb;

Renderbuffer::Renderbuffer(const string& label):
	Bindable<GL_RENDERBUFFER, glGenRenderbuffers, glDeleteRenderbuffers, glBindRenderbuffer>(GL_RENDERBUFFER, label)
{
}

void Renderbuffer::store(GLenum internalformat, i32 width, i32 height)
{
	bind();
	glRenderbufferStorage(type, internalformat, width, height);
}

// TODO: Implement
