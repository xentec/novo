#include "shader.h"

using namespace novo::gl;
using namespace glb;

Shader::Shader(Type shader_type, const string& source, const string& label):
	Object(glCreateShader(shader_type), label)
{
	if(source.length())
		load(source);
}

Shader::Type Shader::getType() const
{
	GLint type = 0;
	glGetShaderiv(id, GL_SHADER_TYPE, &type);
	return static_cast<Type>(type);
}

void Shader::load(const std::string& source) const
{
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
}

bool Shader::compile() const
{
	glCompileShader(id);

	bool ok = isCompiled();
	if(!ok)
		throw OpenGLException(this, fmt::sprintf("failed to compile:\n%s", getInfoLog()));

	return ok;
}

bool Shader::isCompiled() const
{
	GLint status = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	return status;
}

string Shader::getInfoLog() const
{
	GLint length = 0;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

	length--;
	string buffer(length, ' ');
	glGetShaderInfoLog(id, length, nullptr, &buffer[0]);

	return buffer;
}

string Shader::getSource() const
{
	GLint length = 0;
	glGetShaderiv(id, GL_SHADER_SOURCE_LENGTH, &length);

	length--;
	string buffer(length, ' ');
	glGetShaderSource(id, length, nullptr, &buffer[0]);

	return buffer;
}

Shader Shader::fromID(u32 id)
{
	GLsizei length = 0;
	GLchar buffer[128];
	glGetObjectLabel(type, id, 128, &length, buffer);

	string label;
	if(length)
		label.assign(buffer, buffer+length);

	return Shader(id, label);
}

Shader::Shader(u32 id, const std::string& label):
	Object(id, label, false)
{}


