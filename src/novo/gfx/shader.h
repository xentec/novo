#pragma once

#include "novo/global.h"
#include "novo/gfx/gl/program.h"

namespace novo {
namespace gfx {

struct Shader
{
	Shader(const string& name = "");

	void load(const string& name);
	void compile();

	void use() const;

	gl::glb::GLenum getPolyMode() const;
	void setPolyMode(const gl::glb::GLenum& value);

	gl::Uniform operator[](string name);
private:
	gl::Program prog;
	gl::glb::GLenum polyMode;
	std::unordered_map<gl::Shader::Type, gl::Shader> shaders;
};

}}
