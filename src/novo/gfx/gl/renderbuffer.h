#pragma once

#include "bindable.h"

namespace novo {
namespace gl {

struct Renderbuffer : Bindable<glb::GL_RENDERBUFFER, glb::glGenRenderbuffers, glb::glDeleteRenderbuffers, glb::glBindRenderbuffer>
{
	Renderbuffer(const string& label = "");

	void store(glb::GLenum internalformat, i32 width, i32 height);
};

}}
