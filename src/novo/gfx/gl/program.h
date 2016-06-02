#pragma once

#include "object.h"
#include "shader.h"
#include "uniform.h"

#include <unordered_map>

namespace novo {
namespace gl {

using Attribute = glb::GLint;

struct Program : Object<glb::GL_PROGRAM, glb::glDeleteProgram>
{
	Program(const string& label = "");

	void attach(const Shader& shader);
	void detach(Shader::Type shader_type);
	void detach(const Shader& shader);

	bool link() const;
	void use() const;

	bool isLinked() const;
	string getInfoLog() const;
	std::unordered_map<Shader::Type, Shader> getShaders() const;

	void setFragDataLocation(u32 color_number, const string& name);

	Attribute getAttribute(const string& name) const;

	Uniform getUniform(const string& name) const;
	Uniform getUniform(i32 uniform_id) const;

	friend struct Uniform;
};

}}
