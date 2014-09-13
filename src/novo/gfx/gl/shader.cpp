#include "shader.h"

#include "names.h"

#include <novo/io.h>

using namespace novo::gl;
using novo::io::File;

Shader::Shader(GLenum shader_type, const string& glsl_source, bool compile_now, const string& label):
	Object(glCreateShader(shader_type), label),
	type(shader_type), source(glsl_source), compiled(false)
{
	if(source.size() && compile_now)
		compile(source);
}

GLenum Shader::getType() const
{
	return type;
}

void Shader::compile(const string& glsl_source) {
	if(glsl_source.size())
		source = glsl_source;

	const GLchar* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);

	compiled = false;
	glCompileShader(id);
	GLint status = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if(!status) {
		GLint length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		string buffer(length, ' ');
		glGetShaderInfoLog(id, length, nullptr, &buffer[0]);

		throw OpenGLException(this, "failed to compile");
	}
	compiled = true;
}

bool Shader::isCompiled() const
{
	return compiled;
}

Shader Shader::load(GLenum shader_type, const string& path, bool compile_now, const std::string& label)
{
	// TODO: Ressource management
	static const string prefix = "res/shaders/";

	return Shader(shader_type, File::getText(prefix + path), compile_now, label);
}

