#include "obj.h"

#include <novo/io.h>
#include <novo/gfx/gl/debug.h>

#include <GL/glew.h>

namespace novo {
namespace graphics {
namespace util {


void createBuffers(const std::vector<GLuint*>& objPtrs) {
	std::vector<GLuint> obj(objPtrs.size());

	glGenBuffers(obj.size(), &*obj.begin());

	for(uint i = 0; i < objPtrs.size(); i++) {
		*(objPtrs[i]) = obj[i];
	}
}

void destroyBuffers(const std::vector<GLuint>& obj) {
	glDeleteBuffers(obj.size(), &*obj.begin());
}

string glGetStringX(GLenum type) {
	const char* str = reinterpret_cast<const char*>(glGetString(type));
	return string(str ?: "");
}


GLuint createShader(GLenum type, const string& source) {
	GLuint shader = glCreateShader(type);

	const GLchar* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);

	glCompileShader(shader);
	GLint ok;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

	if(!ok) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		string buffer;
		buffer.resize(length);
		glGetShaderInfoLog(shader, length, nullptr, &*buffer.begin());

		//throw new std::runtime_error(GL.Shader[type] ~ " shader failed!\n" std::string(buffer));
		throw std::runtime_error(GL.Shader[type] + string(" failed!\n") + string(buffer));
	}

	return shader;
}

GLuint createProgram(GLint vertexShader, GLint fragmentShader, GLint geometryShader) {
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if(geometryShader >= 0)
		glAttachShader(shaderProgram, geometryShader);

	// Setting color vector output in fragment shader to outColor
	glBindFragDataLocation(shaderProgram, 0, "color");

	glLinkProgram(shaderProgram);
	return shaderProgram;
}

GLuint createProgram(const string& vertexSource, const string& fragmentSource, const string& geometrySource) {
	GLint vertex = createShader(GL_VERTEX_SHADER, vertexSource);
	GLint fragment = createShader(GL_FRAGMENT_SHADER, fragmentSource);

	GLint geometry = -1;
	if(geometrySource.length()) {
		geometry = createShader(GL_GEOMETRY_SHADER, geometrySource);
	}

	GLuint prog = createProgram(vertex,fragment,geometry);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if(geometrySource.length())
		glDeleteShader(geometry);
	return prog;
}

GLuint createProgramFromFiles(const string& vertexPath, const string& fragmentPath, const string& geometryPath) {
	using ::novo::util::loadFile;

	// TODO: Ressource management
	static const string prefix = "res/shaders/";
	if(geometryPath.length())
		return createProgram(loadFile(prefix + vertexPath), loadFile(prefix + fragmentPath), loadFile(prefix + geometryPath));
	else
		return createProgram(loadFile(prefix + vertexPath), loadFile(prefix + fragmentPath));
}

}}}
