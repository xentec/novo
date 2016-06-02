#pragma once

#include "object.h"

namespace novo {
namespace gl {


struct Shader : Object<glb::GL_SHADER, glb::glDeleteShader>
{
	using Type = glb::GLenum;

	Shader(Type shader_type, const string& source = "", const string& label = "");

	Type getType() const;

	void load(const string& source) const;
	bool compile() const;

	bool isCompiled() const;
	string getInfoLog() const;
	string getSource() const;

	static Shader fromID(u32 id);
private:
	Shader(u32 id, const string& label);
};

namespace ShaderType {
#define GL(d) GLenum::GL_##d##_SHADER
	using glb::GLenum;
	static const Shader::Type
		Vertex             = GL(VERTEX),
		Fragment           = GL(FRAGMENT),
		TesselationControl = GL(TESS_CONTROL),
		TesselationEval    = GL(TESS_EVALUATION),
		Geometry           = GL(GEOMETRY),
		Compute            = GL(COMPUTE);
#undef GL
}

}}
