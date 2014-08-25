#include "program.h"

using namespace novo::gl;

Program::Program():
	Object(glCreateProgram(), glDeleteProgram), linked(false)
{
}

Program::Program(Shader& vertex, Shader& fragment, bool link_now):
	Program()
{
	attach(vertex);
	attach(fragment);
	if(link_now)
		link();
}

void Program::attach(Shader shader)
{
	if(!shader.isCompiled())
		shader.compile();

	glAttachShader(id, shader);

	shaders.emplace(shader.getType(), shader);
}

void Program::detach(const Shader& shader)
{
	glDetachShader(id, shader);
}

void Program::detach(GLenum shader)
{
	glDetachShader(id, shaders[shader]);
	shaders.erase(shader);
}

void Program::link()
{
	linked = false;
	glLinkProgram(id);

	GLint status = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &status);

	if(!status) {
		GLint length = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

		string buffer(length, ' ');
		glGetProgramInfoLog(id, length, nullptr, &buffer[0]);

		throw std::runtime_error(string("Program ")+getLabel()+string(" failed to link!\n") + buffer);
	}
	linked = true;
}

void Program::use()
{
	if(!linked)
		link();
	glUseProgram(id);
}

void Program::bindFragDataLocation(u32 color_number, const string& name)
{
	glBindFragDataLocation(id, color_number, name.c_str());
}

Attribute Program::getAttribute(const string& name) const
{
	return glGetAttribLocation(id, name.c_str());
}

Uniform Program::getUniform(const string& name) const
{
	return glGetUniformLocation(id, name.c_str());
}

void Program::setUniform(Uniform location, GLsizei count, const GLfloat& value) { glProgramUniform1fv(id, location, count, &value); }
void Program::setUniform(Uniform location, GLsizei count, const GLdouble& value) { glProgramUniform1dv(id, location, count, &value); }
void Program::setUniform(Uniform location, GLsizei count, const GLint& value) { glProgramUniform1iv(id, location, count, &value); }
void Program::setUniform(Uniform location, GLsizei count, const GLuint& value) { glProgramUniform1uiv(id, location, count, &value); }

void Program::setUniform(Uniform location, GLsizei count, const vec2& value) { glProgramUniform2fv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dvec2& value) { glProgramUniform2dv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const ivec2& value) { glProgramUniform2iv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const uvec2& value) { glProgramUniform2uiv(id, location, count, value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const vec3& value) { glProgramUniform3fv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dvec3& value) { glProgramUniform3dv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const ivec3& value) { glProgramUniform3iv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const uvec3& value) { glProgramUniform3uiv(id, location, count, value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const vec4& value) { glProgramUniform4fv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dvec4& value) { glProgramUniform4dv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const ivec4& value) { glProgramUniform4iv(id, location, count, value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const uvec4& value) { glProgramUniform4uiv(id, location, count, value_ptr(value)); }


void Program::setUniform(Uniform location, GLsizei count, const mat2& value, bool transpose) { glProgramUniformMatrix2fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat2& value, bool transpose) { glProgramUniformMatrix2dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat3& value, bool transpose) { glProgramUniformMatrix3fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat3& value, bool transpose) { glProgramUniformMatrix3dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat4& value, bool transpose) { glProgramUniformMatrix4fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat4& value, bool transpose) { glProgramUniformMatrix4dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }


void Program::setUniform(Uniform location, GLsizei count, const mat2x3& value, bool transpose) { glProgramUniformMatrix2x3fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat2x3& value, bool transpose) { glProgramUniformMatrix2x3dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat3x2& value, bool transpose) { glProgramUniformMatrix3x2fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat3x2& value, bool transpose) { glProgramUniformMatrix3x2dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat2x4& value, bool transpose) { glProgramUniformMatrix2x4fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat2x4& value, bool transpose) { glProgramUniformMatrix2x4dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat4x2& value, bool transpose) { glProgramUniformMatrix4x2fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat4x2& value, bool transpose) { glProgramUniformMatrix4x2dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat3x4& value, bool transpose) { glProgramUniformMatrix3x4fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat3x4& value, bool transpose) { glProgramUniformMatrix3x4dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

void Program::setUniform(Uniform location, GLsizei count, const mat4x3& value, bool transpose) { glProgramUniformMatrix4x3fv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }
void Program::setUniform(Uniform location, GLsizei count, const dmat4x3& value, bool transpose) { glProgramUniformMatrix4x3dv(id, location, count, static_cast<GLboolean>(transpose), value_ptr(value)); }

