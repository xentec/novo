#include "program.h"

using namespace novo::gl;

Program::Program():
	Object(glCreateProgram()), linked(false)
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

Program::~Program()
{
	glDeleteProgram(id);
}

void Program::attach(Shader shader)
{
	if(!shader.isCompiled())
		shader.compile();
	glAttachShader(id, shader);
}

void Program::link()
{
	linked = false;
	glLinkProgram(id);

	GLint status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);

	if(!status) {
		GLint length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

		string buffer(length, ' ');
		glGetProgramInfoLog(id, length, nullptr, &buffer[0]);

		throw std::runtime_error(string("Program ")+label+string(" failed to link!\n") + buffer);
	}
	linked = true;
}

void Program::use()
{
	if(!linked)
		link();
	glUseProgram(id);
}

void Program::setFragDataLocation(u32 color_number, const string& name)
{
	glBindFragDataLocation(id, color_number, name.c_str());
}

