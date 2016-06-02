#include "program.h"

using namespace novo::gl;
using namespace glb;

Program::Program(const string& label):
	Object(glCreateProgram(), label)
{}

void Program::attach(const Shader& shader)
{
	glAttachShader(id, shader);
}

void Program::detach(const Shader& shader)
{
	glDetachShader(id, shader);
}

void Program::detach(Shader::Type shader_type)
{
	glDetachShader(id, getShaders().at(shader_type));
}

bool Program::link() const
{
	glLinkProgram(id);
	bool ok = isLinked();
	if(!ok)
		throw OpenGLException(this, fmt::format("failed to link:\n{}", getInfoLog()));

	return ok;
}

void Program::use() const
{
	glUseProgram(id);
}

bool Program::isLinked() const
{
	GLint status = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	return status;
}

string Program::getInfoLog() const
{
	GLint length = 0;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

	if(length <= 0)
		return string();

	string buffer(length-2, ' ');
	glGetProgramInfoLog(id, length, nullptr, &buffer[0]);
	return buffer;
}

std::unordered_map<Shader::Type, Shader> Program::getShaders() const
{
	std::unordered_map<Shader::Type, Shader> shaders;
	GLuint ids[6];
	GLsizei count = 0;

	glGetAttachedShaders(id, 6, &count, ids);

	for(GLsizei i = 0; i < count; i++)
	{
		Shader s = Shader::fromID(ids[i]);
		shaders.emplace(s.getType(), s);
	}
	return shaders;
}

void Program::setFragDataLocation(u32 color_number, const string& name)
{
	glBindFragDataLocation(id, color_number, name.c_str());
}

Attribute Program::getAttribute(const string& name) const
{
	return glGetAttribLocation(id, name.c_str());
}

Uniform Program::getUniform(const string& name) const
{
	return Uniform(this, glGetUniformLocation(id, name.c_str()));
}

Uniform Program::getUniform(i32 uniform_id) const
{
	return Uniform(this, uniform_id);
}
